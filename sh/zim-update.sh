#imrdr
#!/bin/bash
#coding:utf-8 
### zim_update.sh
cd ~/gitee/mynotebook/Zim/story
git pull
cd ~/gitee/mynotebook/
git pull
    
cd ~/gitee/mynotebook/Zim/story
git add .
git commit -m"commit by xubuntu notebook"
git push
    
cd ~/gitee/mynotebook/
git add .
git commit -m"commit by xubuntu notebook"
git push
