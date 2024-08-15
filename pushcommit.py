from datetime import datetime as dt
import git.index
import git.repo
import sys
import os

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

def git_push(path, repourl, commitmsg, branch, force):
    try:
        repo = git.Repo(path=path)
        for x in repo.index.diff("HEAD"):
            print(x.new_file)
            print(x.b_path)
            
        repo.index.add(['*'])
        repo.index.commit(str(commitmsg))
        origin = repo.remote(name="origin")
        origin.push()
    except Exception as e:
        print('Some error occured while pushing the code \n' + e)    
        
shouldPush = False
forcepush  = False
repopath   = ""
repourl    = ""
commitbranch = "main"
commitmsg  = ""
commitdate = (custom_strftime('{S} %B %H:%M%p %Y', dt.now()))




if(len(sys.argv) <= 3):
    print("No arguments provided")
    print("provide [repo path] [repo url] [commit message] [branch (optional)] [force (optional)]")
    forcepush = False
    
else:
    if(sys.argv[1] is None):
        print("Please enter a repo folder path")
    if(sys.argv[2] is None):
        print("You must enter a github repository url (must end with .git)")
    if(sys.argv[3] is None):
        commitmsg = str(commitdate)
    
    if(sys.argv[1] is not None):
        if(os.path.exists(sys.argv[1])):
            if(is_git_repo(sys.argv[1])):
                repopath = sys.argv[1]
                shouldPush = True
            else:
                print("Folder does not contain a git repository")
        else:
            print("Invalid path")
    if(sys.argv[2] is not None):
        repourl = sys.argv[2]
    if(len(sys.argv) >= 4): # throw away 4th arg
        if(sys.argv[3].lower() == "n" or sys.argv[3].lower() == "no"):
            forcepush = False
        elif(sys.argv[3].lower() == "y" or sys.argv[3].lower == "yes" or sys.argv[3].lower() == "true"):
            forcepush = True

    if(shouldPush):
        git_push(repopath, repourl, commitmsg, commitbranch, forcepush)
        


