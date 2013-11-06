drop database testdb;
create database testdb;
use testdb;

CREATE TABLE account
(
	id		INT AUTO_INCREMENT,
	name		VARCHAR(255),
	password	VARCHAR(255),
	PRIMARY KEY(id)
);

INSERT INTO account(name,password) VALUES('root','root');
