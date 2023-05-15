[user]
        name = EricLiWSL
        email = @.com
[alias]
        co = commit
        st = status
        logl = log --graph --all --oneline
[core]
        quotepath = false
        editor = code --wait --new-window
        excludesfile = ~/.gitignore
[filter "lfs"]
        process = git-lfs filter-process
        required = true
        clean = git-lfs clean -- %f
        smudge = git-lfs smudge -- %f
[diff]
        tool = vscode-diff
[difftool]
        prompt = false
[difftool "vscode-diff"]
        cmd = code --wait --diff $LOCAL $REMOTE
[merge]
        tool = vscode-merge
[mergetool "vscode-merge"]
        cmd = code --wait $MERGED

[init]
        defaultBranch = main
[http]
        sslVerify = false
[https]
        sslVerify = false
[branch]
        autosetuprebase = always