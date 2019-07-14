--
-- File generated with SQLiteStudio v3.2.1 on Sun Jul 14 16:26:47 2019
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
    platform_id INT     REFERENCES platforms (id),
    genre_id    INT     REFERENCES genres (id) 
);

INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (0, 'Dragon Age: Inquisition', 1, 0, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (1, 'Animal Crossing: New Leaf', 1, 1, 1, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (2, 'Dragon Age: Origins', 3, 0, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (4, 'NieR: Automata', 2, 2, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (7, 'The Sims 4', 1, 4, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (16, 'Remember Me', 2, 8, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (17, 'Apex Legends', 1, 9, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (19, 'Dragon''s Dogma', 3, 12, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (20, 'Simcity 4', 2, 6, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (21, 'The Sims 3', 1, 4, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (22, 'The Sims 2', 2, 4, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (23, 'Stardew Valley', 1, NULL, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (24, 'The Sims', 2, 4, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (25, 'Tetris 99', 2, NULL, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (26, 'Fire Emblem: Awakening', 2, 15, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (27, 'Fire Emblem: Fates', 2, 15, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (29, 'Super Mario Sunshine', 2, 17, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (30, 'Beautiful Katamari', 2, 18, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (31, 'Jak & Daxter', 2, 19, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (32, 'Jak II', 2, 19, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (33, 'Jak III', 2, 19, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (34, 'Pokemon Yellow', 2, 20, NULL, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (35, 'Ys Origin', 1, 21, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (38, 'Yakuza 0', 1, 26, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (39, 'Wolfenstein: The New Order', 0, 27, 0, NULL);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (40, 'Wolfenstein: The Old Blood', 0, 27, 0, NULL);

-- Table: genres
DROP TABLE IF EXISTS genres;

CREATE TABLE genres (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);


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
INSERT INTO platforms (id, name) VALUES (2, 'Nintendo Switch');

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
INSERT INTO series (id, name) VALUES (14, 'Tetris');
INSERT INTO series (id, name) VALUES (15, 'Fire Emblem');
INSERT INTO series (id, name) VALUES (16, 'Final Fantasy');
INSERT INTO series (id, name) VALUES (17, 'Super Mario');
INSERT INTO series (id, name) VALUES (18, 'Katamari');
INSERT INTO series (id, name) VALUES (19, 'Jak & Daxter');
INSERT INTO series (id, name) VALUES (20, 'Pokemon');
INSERT INTO series (id, name) VALUES (21, 'Ys');
INSERT INTO series (id, name) VALUES (22, 'Pokemon (old)');
INSERT INTO series (id, name) VALUES (23, 'Hello');
INSERT INTO series (id, name) VALUES (24, 'Hello World');
INSERT INTO series (id, name) VALUES (25, 'Woels');
INSERT INTO series (id, name) VALUES (26, 'Yakuza');
INSERT INTO series (id, name) VALUES (27, 'Wolfenstein');
INSERT INTO series (id, name) VALUES (28, 'Monster Hunter');
INSERT INTO series (id, name) VALUES (29, 'Monster Hun');

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
