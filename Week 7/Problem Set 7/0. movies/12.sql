SELECT title
FROM movies
WHERE id IN (
    SELECT stars.movie_id
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Bradley Cooper'
)
AND id IN (
    SELECT stars.movie_id
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Jennifer Lawrence'
);
