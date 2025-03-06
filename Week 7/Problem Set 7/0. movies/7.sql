SELECT movies.title, ratings.rating FROM ratings JOIN movies ON ratings.movie_id = movies.id WHERE year = 2010 AND rating > 0 ORDER BY ratings.rating DESC, movies.title ASC;
