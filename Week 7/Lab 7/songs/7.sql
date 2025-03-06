SELECT SUM(energy)/COUNT(energy) AS 'Average energy' FROM songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = 'Drake';
