#include "../include/song.hpp"
//Song Implementations
Song::Song () {}
 //With parameters
Song::Song (const std::string& name,const Song::Length& songLength,const std::string& artist) 
            : name(name), length(songLength), artist(artist) {}

Song::Song (const std::string& name, const size_t& minutes, const size_t& seconds, const std::string& artist) 
            :name(name), length(minutes,seconds), artist(artist) {}
//Getters and setters
//setters
void Song::setName (const std::string& name) {
    this -> name = name;
}

void Song::setLength (const size_t& minutes, const size_t& seconds) {
    this -> length.setLength(minutes, seconds);
}

void Song::setArtist (const std::string& artist) {
    this -> artist = artist;
}
//Getters
std::string Song::getName ()const {
    return name;
}
std::string Song::getArtist ()const {
    return artist;
}
Song::Length Song::getLength ()const {
    return length;
}
//To string method
std::string Song::toString () const {
    return this -> artist + '|' + this -> name + '|' + this -> length.getLength() + '*';
}
//Operator overload
//Assign operator
Song& Song::operator = (const Song& song) {
    this ->name = song.getName();
    this ->artist = song.getArtist();
    this -> length = song.getLength();

    return *this;
}
//Logic operator
bool Song::operator == (const Song& song)const {
    return this -> length == song.getLength() 
           and this -> artist == song.getArtist() 
           and this -> name == song.getName();
}
//Stream operator
std::ostream& operator << (std::ostream& os,const Song& song) {

    std::string buffer = std::format ("{}|{}|{}*",song.getName(),song.getArtist(),song.getLength().getLength());    

    os << buffer;

    return os;
}
std::istream& operator >> (std::istream& is, Song& song) {
    std::string buffer;
    getline(is,buffer,'|');
    if (buffer.size()) {
        song.setName(buffer);
        getline(is,buffer,'|');
        song.setArtist(buffer);
        is >> song.length;
        getline(is,buffer,'*');
    }
    return is;
}
//Comparison methods
short Song::compareByName (const Song& firstSong,const Song& secondSong) {
    if (firstSong.getName() > secondSong.getName()) return 1;
    else if (firstSong.getName() < secondSong.getName()) return -1;
    else return 0;
}
short Song::compareByArtist (const Song& firstSong, const Song& secondSong) {
    if (firstSong.getArtist() > secondSong.getArtist()) return 1;
    else if (firstSong.getArtist() < secondSong.getArtist()) return -1;
    else return 0;
}
short Song::compareByLength (const Song& firstSong,const Song& secondSong) {
    if (firstSong.getLength() > secondSong.getLength()) return 1;
    else if (firstSong.getLength() < secondSong.getLength()) return -1;
    else return 0;
}
//Length implementations
//Constructors
Song::Length::Length () {}

Song::Length::Length (const size_t& minutes, const size_t& seconds) : minutes(minutes), seconds(seconds) {}
//Setters
void Song::Length::setMinutes (const size_t& minutes) {
    this -> minutes = minutes;
}

void Song::Length::setSeconds (const size_t& seconds) {
    if (seconds > this -> MAX_SECONDS){
        this -> seconds = 59;   
    }
    else {
        this -> seconds = seconds;
    }
}

void Song::Length::setLength (const size_t& minutes, const size_t& seconds) {
    this -> minutes = minutes;
    this -> seconds = seconds;
}
//Getters
size_t Song::Length::getMinutes () const{
    return minutes;
}

size_t Song::Length::getSeconds () const{
    return seconds;
}

std::string Song::Length::getLength ()const{
    return std::format ("{}:{}.",minutes,seconds);
}

Song::Length& Song::Length::operator = (const Song::Length& length) {
    this -> minutes = length.minutes;
    this -> seconds = length.seconds;

    return *this;
}

Song::Length Song::Length::operator + (const Song::Length& length) {
    size_t seconds, minutes = this-> minutes + length.getMinutes();

    if ((seconds = (this->getSeconds() + length.getSeconds()))/60 >= 1.0) minutes += seconds%60; 

    Song::Length auxLength = Song::Length (minutes,seconds);

    return auxLength;
}

bool Song::Length::operator == (const Song::Length& length) const{
    return this -> minutes*60 + seconds == length.getMinutes()*60 + length.getSeconds();
}

bool Song::Length::operator != (const Song::Length& length) const {
    return !(*this == length);
}

bool Song::Length::operator > (const Song::Length& length) const {
    return this -> minutes*60 + this -> seconds > length.getMinutes()*60 + length.getSeconds();
}

bool Song::Length::operator <= (const Song::Length& length) const {
    return !(*this > length);
}

bool Song::Length::operator < (const Song::Length& length) const {
    return this -> minutes*60 + this -> seconds < length.getMinutes()*60 + length.getSeconds();
}

bool Song::Length::operator >= (const Song::Length& length) const {
    return !(*this < length);
}

std::ostream& operator << (std::ostream& os,const Song::Length& length) {
    std::string buffer = std::format ("{}:{}.",length.getMinutes(),length.getSeconds());
    os << buffer;
    return os;
}

std::istream& operator >> (std::istream& is, Song::Length& length) {
    std::string buffer;
    getline (is,buffer,':');

    if (buffer.size()) {
        length.setMinutes(stoi(buffer));
        getline(is,buffer,'.');
        length.setSeconds(stoi(buffer));
    }

    return is;
}