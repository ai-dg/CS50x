-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

SELECT name, year, month, day FROM interviews WHERE day = 28 AND month = 7;

SELECT name, year, month, day, transcript FROM interviews WHERE day = 28 AND month = 7;

SELECT origin_airport_id, destination_airport_id
FROM flights WHERE day = 29 and month = 7;

SELECT full_name FROM airports
JOIN flights ON airports.id = flights.origin_airport_id
WHERE airports.id IN (
    SELECT origin_airport_id FROM flights WHERE day = 29 and month = 7
);

SELECT full_name FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE airports.id IN (
    SELECT destination_airport_id FROM flights WHERE day = 29 and month = 7
);

SELECT full_name FROM airports
WHERE airports.id = 6 OR airports.id = 11
OR airports.id = 4 OR airports.id = 1 OR airports.id = 9;

SELECT activity, license_plate, hour, minute FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10;

SELECT account_number, amount FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28
AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';

SELECT name, license_plate FROM people
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28
    AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street'
);

SELECT id, caller, receiver, duration FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

SELECT phone_number FROM people WHERE name = 'Diana';

SELECT phone_number FROM people WHERE name = 'Taylor';

SELECT phone_number FROM people WHERE name = 'Bruce';
SELECT phone_number FROM people WHERE name = 'Iman';
SELECT phone_number FROM people WHERE name = 'Luca';

SELECT name FROM people WHERE phone_number = '(676) 555-6554';
SELECT name FROM people WHERE phone_number = '(725) 555-3243';

SELECT name FROM people WHERE phone_number = '(375) 555-8161';

SELECT name, passport_number FROM people WHERE name = 'Diana';
SELECT name, passport_number FROM people WHERE name = 'James';
SELECT name, passport_number FROM people WHERE name = 'Taylor';
SELECT name, passport_number FROM people WHERE name = 'Philip';

SELECT name, passport_number FROM people WHERE name = 'Bruce';
SELECT name, passport_number FROM people WHERE name = 'Robin';


SELECT full_name FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
WHERE airports.id IN (
    SELECT destination_airport_id FROM flights WHERE day = 29 and month = 7
) AND passengers.passport_number = '3592750733';

SELECT full_name FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
WHERE airports.id IN (
    SELECT destination_airport_id FROM flights WHERE day = 29 and month = 7
) AND passengers.passport_number = '2438825627';


SELECT full_name FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
WHERE airports.id IN (
    SELECT destination_airport_id FROM flights WHERE day = 29 and month = 7
) AND passengers.passport_number = '1988161715';


SELECT full_name FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
WHERE airports.id IN (
    SELECT destination_airport_id FROM flights WHERE day = 29 and month = 7
) AND passengers.passport_number = '3391710505';


SELECT full_name, city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
WHERE airports.id IN (
    SELECT destination_airport_id FROM flights WHERE day = 29 and month = 7
) AND passengers.passport_number = '5773159633';
