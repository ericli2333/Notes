echo $(date +"%Y-%m-%d %H:%M:%S") | tee -a sync.log
git pull gitlab_nju main | tee -a sync.log
git push gitlab_nju main | tee -a sync.log
git pull github main | tee -a sync.log
git push github main | tee -a sync.log
git pull gitlab_my main | tee -a sync.log
git push gitlab_my main | tee -a sync.log