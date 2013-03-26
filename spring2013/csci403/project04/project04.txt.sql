CREATE TABLE movies (
	id INTEGER PRIMARY KEY UNIQUE,
	name TEXT,
	personal_rating INTEGER NOT NULL CHECK (personal_rating >= 1 and personal_rating <= 5),
	date_seen  DATE
);

CREATE TABLE species (
	id INTEGER PRIMARY KEY UNIQUE,
	movie_id INTEGER NOT NULL,
	genre_id INTEGER NOT NULL,
	FOREIGN KEY(movie_id) REFERENCES movies(id),
	FOREIGN KEY(genre_id) REFERENCES genres(id)
);

CREATE TABLE genres (
	id INTEGER PRIMARY KEY UNIQUE,
	type TEXT NOT NULL
);

CREATE TABLE starring (
	id INTEGER PRIMARY KEY UNIQUE,
	movie_id INTEGER NOT NULL,
	actor_id INTEGER NOT NULL,
	FOREIGN KEY(movie_id) REFERENCES movies(id),
	FOREIGN KEY(actor_id) REFERENCES actors(id)
);

CREATE TABLE actors (
	id INTEGER PRIMARY KEY UNIQUE,
	first_name TEXT,
	last_name TEXT,
	gender TEXT,
	age INTEGER
);
