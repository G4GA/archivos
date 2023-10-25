#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <format>

class Song {
    public:
        //Nested class song length
        class Length {
            public:
                //Constructor
                Length ();
                Length (const size_t&, const size_t&);
                //Setters
                void setMinutes (const size_t&);
                void setSeconds (const size_t&);
                void setLength (const size_t&, const size_t&);
                //Getters
                size_t getMinutes () const;
                size_t getSeconds () const;
                std::string getLength ()const;
                //Operator overload
                //Assign operator
                Song::Length& operator = (const Song::Length&);
                //Aritmetic operators
                Song::Length operator + (const Song::Length&);
                //Logic operators
                bool operator == (const Song::Length&)const;
                bool operator != (const Song::Length&) const;
                bool operator < (const Song::Length&)const;
                bool operator > (const Song::Length&)const;
                bool operator <= (const Song::Length&)const;
                bool operator >= (const Song::Length&)const;
                //Stream operators
                friend std::ostream& operator << (std::ostream&,const Song::Length&);
                friend std::istream& operator >> (std::istream&, Song::Length&);
            private:
                //Constants
                const size_t MAX_SECONDS = 59;
                //Atributtes
                size_t minutes;
                size_t seconds;
        };
        //constructor
        //Empty song object
        Song ();
        //With parameters
        Song (const std::string& name,const Song::Length& songLength,const std::string& artist);
        Song (const std::string& name, const size_t& minutes, const size_t& seconds, const std::string& artist);
        //Getters and setters
        //setters
        void setName (const std::string&);
        void setLength (const size_t&, const size_t&);
        void setArtist (const std::string&);
        //Getters
        std::string getName ()const;
        std::string getArtist ()const;
        Song::Length getLength ()const;
        //To string method
        std::string toString ()const;
        //Operator overload
        //Assign operator
        Song& operator = (const Song&);
        //Comparison operator
        bool operator == (const Song&)const; 
        bool operator < (const Song&)const;
        bool operator <= (const Song&)const;
        bool operator > (const Song&)const;
        bool operator >= (const Song&)const;
        //Stream operators
        friend std::ostream& operator << (std::ostream&,const Song&);
        friend std::istream& operator >> (std::istream&, Song&);
        //Comparison methods
        static short compareByName (const Song&,const Song&);
        static short compareByArtist (const Song&, const Song&);
        static short compareByLength (const Song&,const Song&);
    private:
        //Atributtes
        std::string name;
        Song::Length length;
        std::string artist;
};