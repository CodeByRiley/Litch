import git
from datetime import datetime as dt
import sys
import os

import git.repo

def suffix(d):
    return {1:'st',2:'nd',3:'rd'}.get(d%20, 'th')

def custom_strftime(format, t):
    return t.strftime(format).replace('{S}', str(t.day) + suffix(t.day))

def is_git_repo(path):
    try:
        _ = git.Repo(path).git_dir
        return True
    except git.exc.InvalidGitRepositoryError:
        return False

def git_push(path, commitmsg, branch):
    try:
        repo = git.Repo(path)
        if(repo.branches.__contains__(branch)):
           repo.active_branch = branch
        else:
            print(f"Git repository doesn\'t have a {branch}")
        repo.git.add(update=True)
        repo.index.commit(commitmsg)
        origin = repo.remote(name='origin')
        origin.push()
    except:
        print('Some error occured while pushing the code')    

repopath = ""
repourl = ""
commitdate = (custom_strftime('{S} %B %H:%M%p %Y', dt.now()))

if(sys.argv[1] is None and sys.argv[2] is None and sys.argv[3] is None):
    print("No arguments provided")
    print("provide [repo path] [repo url] [branch]")
    
if(sys.argv[1] is None):
    print("Please enter a repo folder path")

if(sys.argv[1] is not None):
    if(os.path.exists(sys.argv[1])):
        if(is_git_repo(sys.argv[1])):
            repopath = sys.argv[1]
            print(f"Adding files from {sys.argv[1]}")
        else:
            print("Folder does not contain a git repository")
    else:
        print("Invalid path")
if(sys.argv[2] is None):
    print("You must enter a github repository url (must end with .git)")