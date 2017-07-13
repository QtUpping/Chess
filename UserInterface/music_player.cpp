#include "music_player.h"
#include<QApplication>
#include<QString>
music_player::music_player()
{
    QString runPath;
    runPath=QApplication::applicationDirPath();
    player=new QMediaPlayer;
    list=new QMediaPlaylist;
    list->addMedia(QUrl::fromLocalFile(runPath+"/Oh.mp3"));
    player->setPlaylist(list);
    player->setVolume(60);
}
void music_player::Play_in_loop()
{
    list->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(list);
    player->play();
}
void music_player::Play_stop()
{
    player->pause();
}
