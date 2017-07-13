#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H
#include<QMediaPlayer>
#include<QMediaPlaylist>

class music_player
{
public:
    music_player();
    void Play_in_loop();
    void Play_stop();
private:
    QMediaPlayer * player;
    QMediaPlaylist * list;
};


#endif // MUSIC_PLAYER_H
