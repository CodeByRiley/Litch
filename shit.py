import git 
repo = git.Repo('G:\Projects\Coding\Projects\CPLUSPLUS\Tinkering\wabble') 
  
# Do some changes and commit
repo.git.add(u=True)
print('Files Added Successfully') 
repo.index.commit('Initial commit on new branch') 
print('Commited successfully')