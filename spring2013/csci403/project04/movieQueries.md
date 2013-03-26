==========================
MARIA DESLIS
CSCI403 BAKOS SPRING 2012
PROJECT04
QUERIES
==========================

INSERT INTO movies (name, personal_rating, date_seen)
SELECT "Babel", "****", "1/1/14"
UNION SELECT "Drunken Master", "****", "1/1/14"
UNION SELECT "Juice", "***", "1/2/14"
UNION SELECT "Dodgeball", "*", "1/3/14"
UNION SELECT "Star Wars", "****", "1/5/14"
UNION SELECT "Bullitt", "***", "1/6/14"
UNION SELECT "Hackers", "**", "1/7/14"
UNION SELECT "Wargames", "**", "1/8/14";


INSERT INTO actors (first_name, last_name, gender, age)
SELECT "Cate","Blanchett","F","40"
UNION SELECT "Jackie","Chan","M","55"
UNION SELECT "Queen","Latifah","F","40"
UNION SELECT "David","Hasselhoff","M","59"
UNION SELECT "Mark","Hamill","M","60"
UNION SELECT "Steve", "McQueen", "M", "??";


INSERT INTO genres (type)
SELECT "Twisted Romance"
UNION SELECT "Excessive Action"
UNION SELECT "Plotless Drivel"
UNION SELECT "Sci-Fi/Fantasy"
UNION SELECT "Computer Geek"
UNION SELECT "Children"
UNION SELECT "Drama Cliche";

INSERT INTO starring (movie_id, actor_id)
SELECT "1","3"
UNION SELECT "2","1"
UNION SELECT "4","4"
UNION SELECT "6","5"
UNION SELECT "7","1"
UNION SELECT "8","6";

INSERT INTO species (movie_id, genre_id)
SELECT "1","7"
UNION SELECT "2","6"
UNION SELECT "3","3"
UNION SELECT "4","7"
UNION SELECT "5","3"
UNION SELECT "6","5"
UNION SELECT "7","4"
UNION SELECT "8","7";


sqlite> SELECT * FROM actors ORDER BY age DESC;
id          first_name  last_name   gender      age       
----------  ----------  ----------  ----------  ----------
4           Steve       McQueen     M           ??        
1           Mark        Hamill      M           60        
5           David       Hasselhoff  M           59        
6           Jackie      Chan        M           55        
3           Queen       Latifah     F           40        
2           Cate        Blanchett   F           40  

sqlite> SELECT * FROM movies ORDER BY personal_rating ASC;
id          name        personal_rating  date_seen 
----------  ----------  ---------------  ----------
6           Dodgeball   *                1/3/14    
5           Wargames    **               1/8/14    
3           Hackers     **               1/7/14    
4           Bullitt     ***              1/6/14    
1           Juice       ***              1/2/14    
8           Drunken Ma  ****             1/1/14    
7           Star Wars   ****             1/5/14    
2           Babel       ****             1/1/14 

sqlite> SELECT * FROM actors WHERE first_name LIKE "%Bacon%";
sqlite> 

sqlite> SELECT * FROM actors WHERE first_name LIKE "%Bacon%";
sqlite> 

sqlite> SELECT AVG(age) FROM actors;
AVG(age)        
----------------
42.3333333333333
sqlite> SELECT MAX(age) FROM actors;
MAX(age)  
----------
??        
sqlite> SELECT MIN(age) FROM actors;
MIN(age)  
----------
40  


