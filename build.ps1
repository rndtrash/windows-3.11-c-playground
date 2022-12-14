#!/usr/bin/env pwsh

# LICENSE: GPLv3
# (c) Ivan Kuzmenko, 2022

param(
	[string]$project = $(Read-Host "Project name (e.g. example)"),
	[string]$language = (Get-Culture).Name
)

$ErrorActionPreference = "Stop" # остановить скрипт при первой же ошибке

try
{
	$l10n_path = $(Resolve-Path "./l10n/$language.ps1")
}
catch
{
	Write-Host "Warning: unable to find a language file for `"$language`", falling back to English..."
	$language = 'en-US'
	$l10n_path = $(Resolve-Path "./l10n/$language.ps1")
}
. $l10n_path

#

function FailOnNonZeroExit
{
	param(
		$command
	)
	Invoke-Expression $command

	if (!$LASTEXITCODE -eq 0)
	{
		throw ($s_command_failed -f $command, $LASTEXITCODE)
	}
}

# Настраиваем переменные для компилятора Open Watcom
$watcom_root = $(Resolve-Path "./watcom")
$watcom_bin = "$watcom_root/bin"

if ($IsLinux)
{
	$watcom_bin += "l"
}
elseif ($IsWindows)
{
	$watcom_bin += "nt"
}
else
{
	throw $s_unknown_os
}

if ([Environment]::Is64BitOperatingSystem)
{
	$watcom_bin += "64"
}

$ENV:PATH = "$watcom_bin;" + $ENV:PATH
$ENV:INCLUDE = "$watcom_root/h;$watcom_root/h/win"
$ENV:WATCOM = $watcom_root

#

Write-Host ($s_building_project -f $project)
$path = $(Resolve-Path "projects/$project")
$ENV:INCLUDE += ";$path"

# Building C/C++ files

$cfiles = $(Get-ChildItem -Path $path -Recurse -Filter "*.c")
if ($cfiles -eq $null) # если у нас нет файлов
{
	$cfiles = @() # сделаем пустым массивом для foreach
}
elseif ($cfiles.GetType() -eq [System.IO.FileInfo]) # если у нас только один файл
{
	$cfiles = @($cfiles) # превращаем в массив опять таки для foreach
}

$cppfiles = $(Get-ChildItem -Path $path -Recurse -Filter "*.cpp")
if ($cppfiles -eq $null) # если у нас нет файлов
{
	$cppfiles = @() # сделаем пустым массивом для foreach
}
elseif ($cppfiles.GetType() -eq [System.IO.FileInfo]) # если у нас только один файл
{
	$cppfiles = @($cppfiles) # превращаем в массив опять таки для foreach
}

Push-Location $path # временно сменим папку на корень проекта

$ofiles = @()

foreach ($cfile in $cfiles)
{
	$ofile = [System.IO.Path]::ChangeExtension($cfile, ".o")
	$ofiles += $ofile
	FailOnNonZeroExit("$watcom_bin/wcc -bt=windows $cfile")
}

foreach ($cppfile in $cppfiles)
{
	$ofile = [System.IO.Path]::ChangeExtension($cfile, ".o")
	$ofiles += $ofile
	FailOnNonZeroExit("$watcom_bin/wpp -bt=windows $cppfile")
}

# Linking

FailOnNonZeroExit("$watcom_bin/wlink FORMat WIndows LIBPath `"$watcom_root/lib386/win;$watcom_root/lib386;$watcom_root/lib286/win;$watcom_root/lib286`" Library windows FILE $($ofiles -join ",") Name $path/$project.exe")

# Building resources

$rcfile = "$project.rc"
if (Test-Path $rcfile)
{
	FailOnNonZeroExit("$watcom_bin/wrc -bt=windows -`"fe=$project.exe`" $rcfile")
}

Pop-Location # возвращаем всё на место

Write-Host ($s_built_successfully -f $project)

#

$dosbox_root = $(Resolve-Path ./dosbox)
$dosbox = "dosbox"

if ($IsWindows)
{
	$dosbox = "$dosbox_root/DOSBox.exe"
}

Write-Host $s_making_windows_image

$temp_path = $(Resolve-Path ./temp)
Set-Content -NoNewline -Path "$temp_path/runapp.bat" -Value "win $project" # -NoNewline потому что под Linux другое окончание строки, не перевариваемое DOS

$win_image = "$(Resolve-Path ./windows)/win311"

[System.IO.File]::Copy("$dosbox_root/modimage_.conf", "$dosbox_root/modimage.conf", $true)
[System.IO.File]::Copy("$path/$project.exe", "$temp_path/$project.exe", $true)
(Get-Content "$dosbox_root/modimage.conf").replace('!WINDOWS_IMAGE', "${win_image}.img").replace("!TEMP", "$temp_path").replace("!PROJECT", "$project") | Set-Content "$dosbox_root/modimage.conf"

[System.IO.File]::Copy("${win_image}${win_suffix}-og.img", "${win_image}.img", $true)

FailOnNonZeroExit("$dosbox -conf $(Resolve-Path ./dosbox)/modimage.conf")

# Настраиваем QEMU

$qemu = "qemu-system-i386"

if ($IsWindows)
{
	$qemu = $(Resolve-Path "./qemu")
	if ([Environment]::Is64BitOperatingSystem)
	{
		$qemu += "64"
	}
	$qemu += "/qemu-system-i386.exe"
}

Write-Host $s_lets_go

FailOnNonZeroExit("$qemu -hda ${win_image}.img -boot ca -cpu pentium -m 32 -vga vmware -net nic,model=pcnet -net user")
