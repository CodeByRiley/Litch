
import git 
  
# Clone a remote repository 
repo_url = "https://github.com/Hardik-Kushwaha/GIT_Python_Automation"
local_path = "/home/hardik/GFG_Temp/Cloned_Repo"
repo = git.Repo.clone_from(repo_url, local_path) 
print(f'Repository Cloned at location: {local_path}') 