CREATE TABLE zoos (
id INTEGER PRIMARY KEY UNIQUE,
name TEXT NOT NULL
);

CREATE TABLE habitats (
id INTEGER PRIMARY KEY UNIQUE,
name TEXT NOT NULL,
capacity INTEGER NOT NULL CHECK ( capacity >= 1 and capacity <= 50 ),
location TEXT NOT NULL,
zoo_id INTEGER NOT NULL,
FOREIGN KEY(zoo_id) REFERENCES zoo(id)
);

CREATE TABLE animals (
id INTEGER PRIMARY KEY UNIQUE,
name TEXT NOT NULL,
cuteness INTEGER NOT NULL CHECK ( cuteness >= 1 and cuteness <= 10 ),
habitat_id INTEGER NOT NULL,
FOREIGN KEY(habitat_id) REFERENCES habitats(id)
);

CREATE TABLE feed (
id INTEGER PRIMARY KEY UNIQUE,
name TEXT NOT NULL,
delicious TEXT NOT NULL CHECK ( "yes" OR "no" )
);

CREATE TABLE eat (
id INTEGER PRIMARY KEY UNIQUE,
feed_id INTEGER NOT NULL,
animal_id INTEGER NOT NULL,
FOREIGN KEY(feed_id) REFERENCES feed(id),
FOREIGN KEY(animal_id) REFERENCES animals(id)
);

CREATE TABLE users (
id INTEGER PRIMARY KEY UNIQUE,
credential_id INTEGER NOT NULL,
FOREIGN KEY(credential_id) REFERENCES credentials(id)
);

CREATE TABLE credentials (
id INTEGER PRIMARY KEY UNIQUE,
user_id INTEGER NOT NULL,
username TEXT NOT NULL CHECK(LENGTH(username) BETWEEN 9 and 16),
password TEXT NOT NULL CHECK(LENGTH(password) BETWEEN 9 and 16),
FOREIGN KEY(user_id) REFERENCES users(id)
);

CREATE TABLE favors (
id INTEGER PRIMARY KEY UNIQUE,
user_id INTEGER NOT NULL,
animal_id INTEGER NOT NULL,
FOREIGN KEY(user_id) REFERENCES users(id),
FOREIGN KEY(animal_id) REFERENCES animal(id)
);