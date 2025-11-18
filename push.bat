@echo off
set /p branch_name=Enter branch name (default is 'main'):
if "%branch_name%"=="" set branch_name=main
git checkout %branch_name%
if errorlevel 1 (
    echo Branch '%branch_name%' does not exist. Creating a new branch.
    git checkout -b %branch_name%
)
echo Switched to branch '%branch_name%'.
set /p commit_msg=Enter commit: 
git add .
git commit -m "%commit_msg%"
git push origin %branch_name%
pause