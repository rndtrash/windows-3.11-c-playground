@echo off
@rem From IDE:  name=%1, file_with_message=%2, project=%3, target=%4
git add %1
git commit -t %2
