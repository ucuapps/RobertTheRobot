# RobertTheRobot

Robert the hardware mobile robot

[![License](https://img.shields.io/github/license/ucuapps/robert.svg)](https://github.com/ucuapps/robert/blob/kinetic-devel/LICENSE)


## Docker
For convenience it is recommended to use Docker containers.
Please follow these steps to run Docker container on your machine.

 1. Install Desktop OS Ubuntu Trusty or Xenial on your machine or in virtual machine
 2. Install Docker-CE using these [instructions](https://docs.docker.com/engine/installation/linux/docker-ce/ubuntu/)
 3. In order to executed Docker without sudo please execute
```bash
sudo usermod -aG docker $USER
```
 4. Logout and login to your machine again :)
 5. For development [the following](http://hub.docker.com/r/lyubomyrd/roberttherobot/) docker container was used.
 6. To pull it please run
```bash
docker pull lyubomyrd/roberttherobot:latest
```
 7. Use the following command to start Docker container
```bash
docker run -it --privileged --name rtr_dev -p 8080:8080 -e DISPLAY -e LOCAL_USER_ID=$(id -u) -v /tmp/.X11-unix:/tmp/.X11-unix:rw lyubomyrd/roberttherobot:latest
```
 8. Black window of [Terminator](https://gnometerminator.blogspot.com/p/introduction.html) UI console will appear after some time.
 9. You can use it's features to [split terminal window](https://linux.die.net/man/1/terminator) into smaller terminals and run few commands in parallel (Ctrl+Shift+E).
 10. If you want to run real robot add user to dialout group and restart Docker container
```bash
sudo usermod -a -G dialout user
```

In order to relaunch docker container after you closed Terminator window or rebooted machine please run
```bash
docker start rtr_dev
```
After some time Terminator window will reappear.

## IDEs

In case if you want to run PyCharm in Docker container please run

```bash
pycharm
```

To launch QtCreator please run

```bash
qtcreator
```

For VSCode type
```bash
vscode
```

