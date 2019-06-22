--
-- File generated with SQLiteStudio v3.2.1 on Fri Jun 21 20:46:30 2019
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: games
DROP TABLE IF EXISTS games;

CREATE TABLE games (
    id          INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                        NOT NULL
                        DEFAULT (0),
    name        TEXT    NOT NULL ON CONFLICT ROLLBACK,
    status_id   INT     REFERENCES status (id),
    series_id   INT     REFERENCES series (id),
    platform_id INT     REFERENCES platforms (id) 
);

INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (0, 'Dragon Age: Inquisition', 1, 0, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (1, 'Animal Crossing: New Leaf', 1, 1, 1);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (2, 'Dragon Age: Origins', 3, 0, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (4, 'NieR: Automata', 1, 2, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (7, 'The Sims 4', 1, 4, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (16, 'Remember Me', 2, 8, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (17, 'Apex Legends', 1, 9, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (19, 'Dragon''s Dogma', 3, 12, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (20, 'Simcity 4', 2, 6, 0);
INSERT INTO games (id, name, status_id, series_id, platform_id) VALUES (21, 'The Sims 3', 3, 4, 0);

-- Table: platforms
DROP TABLE IF EXISTS platforms;

CREATE TABLE platforms (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);

INSERT INTO platforms (id, name) VALUES (0, 'PC');
INSERT INTO platforms (id, name) VALUES (1, 'Nintendo 3DS');

-- Table: series
DROP TABLE IF EXISTS series;

CREATE TABLE series (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);

INSERT INTO series (id, name) VALUES (0, 'Dragon Age');
INSERT INTO series (id, name) VALUES (1, 'Animal Crossing');
INSERT INTO series (id, name) VALUES (2, 'NieR');
INSERT INTO series (id, name) VALUES (4, 'The Sims');
INSERT INTO series (id, name) VALUES (6, 'Simcity');
INSERT INTO series (id, name) VALUES (7, 'The Simsg');
INSERT INTO series (id, name) VALUES (8, 'Remember Me');
INSERT INTO series (id, name) VALUES (9, 'Apex Legends');
INSERT INTO series (id, name) VALUES (12, 'Dragon''s Dogma');
INSERT INTO series (id, name) VALUES (13, 'Apex');

-- Table: status
DROP TABLE IF EXISTS status;

CREATE TABLE status (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name         UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);

INSERT INTO status (id, name) VALUES (0, 'Not Started');
INSERT INTO status (id, name) VALUES (1, 'Playing');
INSERT INTO status (id, name) VALUES (2, 'Finished');
INSERT INTO status (id, name) VALUES (3, 'On Hold');
INSERT INTO status (id, name) VALUES (4, 'Dropped');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
