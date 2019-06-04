--
-- File generated with SQLiteStudio v3.2.1 on Thu May 30 17:30:02 2019
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: games
DROP TABLE IF EXISTS games;

CREATE TABLE games (
    id        INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                      NOT NULL
                      DEFAULT (0),
    name      TEXT    NOT NULL ON CONFLICT ROLLBACK,
    status_id INT     REFERENCES status (id),
    series_id INT     REFERENCES series (id)
);

INSERT INTO games (id, name, status_id, series_id) VALUES (0, 'Dragon Age: Inquisition', 1, 0);
INSERT INTO games (id, name, status_id, series_id) VALUES (1, 'Animal Crossing: New Leaf', 1, 1);
INSERT INTO games (id, name, status_id, series_id) VALUES (2, 'Dragon Age: Origins', 2, 0);
INSERT INTO games (id, name, status_id, series_id) VALUES (3, 'Remember Me', 2, NULL);
INSERT INTO games (id, name, status_id, series_id) VALUES (4, 'NieR: Automata', 1, 2);
INSERT INTO games (id, name, status_id, series_id) VALUES (5, 'Cities: Skylines', 1, NULL);

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
