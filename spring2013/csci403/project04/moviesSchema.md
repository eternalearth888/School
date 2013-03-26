==========================
MARIA DESLIS
CSCI403 BAKOS SPRING 2012
PROJECT04
MOVIES.DB .SCHEMA
==========================
sqlite> .schema
CREATE TABLE actors (
	id INTEGER PRIMARY KEY UNIQUE,
	first_name TEXT NOT NULL,
	last_name TEXT NOT NULL,
	gender TEXT NOT NULL,
	age INTEGER NOT NULL
);
CREATE TABLE genres (
	id INTEGER PRIMARY KEY UNIQUE,
	type TEXT NOT NULL
);
CREATE TABLE movies (
	id INTEGER PRIMARY KEY UNIQUE,
	name TEXT NOT NULL,
	personal_rating INTEGER NOT NULL CHECK (personal_rating >= 1 and personal_rating <= 5),
	date_seen  DATE NOT NULL
);
CREATE TABLE species (
	id INTEGER PRIMARY KEY UNIQUE,
	movie_id INTEGER NOT NULL,
	genre_id INTEGER NOT NULL,
	FOREIGN KEY(movie_id) REFERENCES movies(id),
	FOREIGN KEY(genre_id) REFERENCES genres(id)
);
CREATE TABLE starring (
	id INTEGER PRIMARY KEY UNIQUE,
	movie_id INTEGER NOT NULL,
	actor_id INTEGER NOT NULL,
	FOREIGN KEY(movie_id) REFERENCES movies(id),
	FOREIGN KEY(actor_id) REFERENCES actors(id)
);

