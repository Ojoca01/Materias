CREATE SCHEMA eventos;


CREATE TABLE eventos.usuario(
	login VARCHAR(12),
	senha	VARCHAR(45) NOT NULL,
	data_cadastro DATE,
	email VARCHAR,
	CONSTRAINT pk_usuario PRIMARY KEY (login)
);


CREATE TABLE eventos.emprego(
	id_emprego INT,
	descricao VARCHAR(45),
	salario REAL,
	CONSTRAINT pk_emprego PRIMARY KEY(id_emprego)
);

CREATE TABLE eventos.empresa(
	id_empresa VARCHAR(5),
	nome VARCHAR(50) NOT NULL,
	patrimonio REAL,
	CONSTRAINT pk_empresa PRIMARY KEY(id_empresa)
);


CREATE TABLE eventos.organizador(
	id_organizador VARCHAR(12),
	login  VARCHAR(12),
	emprego INT NOT NULL,
	empresa VARCHAR(5),
	CONSTRAINT pk_organizador PRIMARY KEY(id_organizador),
	CONSTRAINT fk_usuario FOREIGN KEY (login) REFERENCES eventos.usuario(login)
	ON DELETE SET NULL ON UPDATE CASCADE,
	CONSTRAINT fk_emprego FOREIGN KEY (emprego) REFERENCES eventos.emprego(id_emprego)
	ON DELETE SET NULL ON UPDATE CASCADE,
	CONSTRAINT fk_empresa FOREIGN KEY (empresa) REFERENCES eventos.empresa(id_empresa)
	ON DELETE SET NULL ON UPDATE CASCADE
);



CREATE TABLE eventos.cliente(
	id_cliente VARCHAR(12),
	login  VARCHAR(12),
	CONSTRAINT pk_cliente PRIMARY KEY(id_cliente),
	CONSTRAINT fk_usuario FOREIGN KEY (login) REFERENCES eventos.usuario(login)
	ON DELETE SET NULL ON UPDATE CASCADE
	
);



CREATE TABLE eventos.evento(
	id_evento SERIAL,
	titulo	VARCHAR(40) NOT NULL,
	evento_anterior INT,
	empresa VARCHAR(5),
	CONSTRAINT pk_evento PRIMARY KEY (id_evento),
	CONSTRAINT fk_anterior FOREIGN KEY(evento_anterior) REFERENCES eventos.evento(id_evento)
	ON DELETE SET NULL ON UPDATE CASCADE,
	CONSTRAINT fk_empresa FOREIGN KEY(empresa) REFERENCES eventos.empresa(id_empresa)
	ON DELETE SET NULL ON UPDATE CASCADE
);


CREATE TABLE eventos.organizacao(
	id_evento INT NOT NULL,
	id_organizador VARCHAR(12) NOT NULL,
	CONSTRAINT pk_organizacao PRIMARY KEY (id_evento, id_organizador),
	CONSTRAINT fk_evento FOREIGN KEY (id_evento) REFERENCES eventos.evento(id_evento) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT fk_organizador FOREIGN KEY (id_organizador) REFERENCES eventos.organizador(id_organizador) ON DELETE  CASCADE ON UPDATE CASCADE
);



CREATE TABLE eventos.ingresso(
	id_cliente VARCHAR(12),
	id_evento INT,
	valor_ingresso	REAL,
	CONSTRAINT pk_ingresso PRIMARY KEY(id_cliente, id_evento),
	CONSTRAINT fk_evento FOREIGN KEY(id_evento) REFERENCES eventos.evento(id_evento)
	ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT fk_cliente FOREIGN KEY(id_cliente) REFERENCES eventos.cliente(id_cliente)
	ON DELETE CASCADE ON UPDATE CASCADE
);








INSERT INTO eventos.empresa VALUES ('FOX', 'empresa A',  10000);
INSERT INTO eventos.empresa VALUES ('WAR', 'empresa B', 5000);
INSERT INTO eventos.empresa VALUES ('COL', 'empresa C', 20000);
INSERT INTO eventos.empresa VALUES ('UNI', 'empresa D', 50000);
INSERT INTO eventos.empresa VALUES ('PIX', 'empresa E', 10000);
insert into eventos.empresa values ('DIS' , 'empresa F', 3000);

INSERT INTO eventos.emprego VALUES (1, 'Gerente', 5500);
INSERT INTO eventos.emprego VALUES (2, 'Organizador', 2500);
INSERT INTO eventos.emprego VALUES (3, 'Supervisor', 3700);


INSERT INTO eventos.usuario VALUES ('11111111100', 'Prod A', '1980-03-05', 'prodA@email.com');
INSERT INTO eventos.organizador VALUES ('D100', '11111111100', 1 , 'FOX');



INSERT INTO eventos.usuario
    VALUES ('11111111101', 'Prod B', '1980-07-23', 'prodB@email.com');
INSERT INTO eventos.organizador VALUES ('D200', '11111111101', 2, 'FOX');


INSERT INTO eventos.usuario
    VALUES ('11111111102', 'Prod C', '1987-05-12', 'prodc@email.com');
INSERT INTO eventos.organizador VALUES ('D300', '11111111102', 3, 'FOX');


INSERT INTO eventos.usuario
    VALUES ('11111111103', 'Prod D', '1975-01-22', NULL);
INSERT INTO eventos.organizador VALUES ('D400', '11111111103', 1, 'FOX');


INSERT INTO eventos.usuario
    VALUES ('11111111104', 'Prod E', '1980-04-25', 'prodE@email.com');
INSERT INTO eventos.organizador VALUES ('D500', '11111111104', 1, 'FOX');


INSERT INTO eventos.usuario
    VALUES ('11111111105', 'Prod F','1960-03-05', 'prodF@email.com');
INSERT INTO eventos.organizador VALUES ('D600', '11111111105', 1, 'WAR');


INSERT INTO eventos.usuario
    VALUES ('11111111106', 'Prod G','1981-03-05', 'prodG@email.com');
INSERT INTO eventos.organizador VALUES ('D700', '11111111106', 3, 'COL');


INSERT INTO eventos.usuario
    VALUES ('11111111107', 'Prod H','1972-08-3', 'prodh@email.com');
INSERT INTO eventos.organizador VALUES ('D800', '11111111107', 2, 'FOX');


INSERT INTO eventos.usuario
    VALUES ('11111111108', 'Prod A', '1986-04-01', 'prodA2@email.com');
INSERT INTO eventos.organizador VALUES ('D900', '11111111108', 2, 'WAR');


INSERT INTO eventos.usuario
    VALUES ('11111111109', 'Prod I', '1980-03-05', 'prodI@email.com');
INSERT INTO eventos.organizador VALUES('D1001', '11111111109', 3, 'WAR');


INSERT INTO eventos.usuario
    VALUES ('11111111110', 'Prod F', '1981-09-05', 'prodFF@email.com');
INSERT INTO eventos.organizador VALUES('D1100', '11111111110', 2, 'FOX');


INSERT INTO eventos.usuario
    VALUES ('11111111111', 'Prod K', '1980-03-04', 'prodK@email.com');
INSERT INTO eventos.organizador VALUES('D1201', '11111111111', 1, 'WAR');


INSERT INTO eventos.usuario
    VALUES ('11111111112', 'Prod I', '1980-03-05', 'prodI@email.com');
INSERT INTO eventos.organizador VALUES('D1301', '11111111112', 1, 'WAR');


INSERT INTO eventos.usuario
    VALUES ('11111111113', 'Prod G', '1954-06-15', 'prodGA@email.com');
INSERT INTO eventos.organizador VALUES ('D1400', '11111111113', 1, 'COL');


INSERT INTO eventos.usuario
    VALUES ('11111111114', 'Prod P', '1989-11-05', 'prodP@email.com');
INSERT INTO eventos.organizador VALUES ('D1501', '11111111114', 3, 'FOX');



INSERT INTO eventos.usuario
    VALUES ('22222222201', '12345', '1990-03-05', 'csj@email.com');
INSERT INTO eventos.cliente VALUES('C101', '22222222201');

INSERT INTO eventos.usuario
    VALUES ('22222222202', '12345', '1999-09-15', 'bds@email.com');
INSERT INTO eventos.cliente VALUES  ('C102', '22222222202');
	
INSERT INTO eventos.usuario
    VALUES ('22222222203', '12345', '1912-07-23', 'h3@hjg.com');
INSERT INTO eventos.cliente VALUES('C103', '22222222203');
	
INSERT INTO eventos.usuario
    VALUES ('22222222204', '12345', '1939-10-07', 'hhh@hjg.com');
INSERT INTO eventos.cliente VALUES('C104', '22222222204');
	
INSERT INTO eventos.usuario 
	VALUES ('22222222205', '12345', '1985-11-27', 'h35@hjg.com');
INSERT INTO eventos.cliente VALUES('C105', '22222222205');
	
INSERT INTO eventos.usuario
    VALUES ('22222222206', '12345', '1996-12-10', 'A106@hjg.com');
INSERT INTO eventos.cliente VALUES('C106', '22222222206');
	
INSERT INTO eventos.usuario
    VALUES ('22222222207', '12345', '1971-12-26', 'A107@hjg.com');
INSERT INTO eventos.cliente VALUES('C107', '22222222207');
	
INSERT INTO eventos.usuario
    VALUES ('22222222208', 'FOXriamaria', '1950-12-26', 'A108@hjg.com');
INSERT INTO eventos.cliente VALUES('C108', '22222222208');
	
INSERT INTO eventos.usuario
    VALUES ('22222222209', '1', '1950-12-26', 'CL@email.com');
INSERT INTO eventos.cliente VALUES('C109', '22222222209');
	
INSERT INTO eventos.usuario
    VALUES ('22222222210', '1234', '1938-01-10', 'A110@hjg.com');
INSERT INTO eventos.cliente VALUES('C110', '22222222210');
	
INSERT INTO eventos.usuario
    VALUES ('22222222211', '1111','1956-01-10', 'cs@sgbd.com');
INSERT INTO eventos.cliente VALUES('C111', '22222222211');
	
INSERT INTO eventos.usuario
    VALUES ('22222222212', '1234',  '1944-03-24', 'A112@hjg.com');
INSERT INTO eventos.cliente VALUES('C112', '22222222212');
	
INSERT INTO eventos.usuario
    VALUES ('22222222213', '1234', '1965-08-22', 'A113@hjg.com');
INSERT INTO eventos.cliente VALUES('C113', '22222222213');

	
INSERT INTO eventos.evento VALUES(1, 'evento 6', NULL, 'UNI');
INSERT INTO eventos.evento VALUES(2, 'evento 7', NULL,'UNI');
INSERT INTO eventos.evento VALUES(3, 'evento 111', 1, 'UNI');

INSERT INTO eventos.evento VALUES(4, 'evento 8', 2, 'UNI');
INSERT INTO eventos.evento VALUES(5, 'evento 9', 2, 'UNI');

INSERT INTO eventos.evento VALUES(6, 'evento 33', NULL, 'UNI');
INSERT INTO eventos.evento VALUES(7, 'evento 6', NULL, 'UNI');
INSERT INTO eventos.evento VALUES(8, 'evento 7', NULL,'UNI');

INSERT INTO eventos.evento VALUES(9, 'evento 79', 2, 'UNI');
INSERT INTO eventos.evento VALUES(10, 'evento 80', 9, 'UNI');
INSERT INTO eventos.evento VALUES(11, 'evento 81', 10, 'UNI');

INSERT INTO eventos.evento VALUES(12, 'evento 98', NULL, 'UNI');
INSERT INTO eventos.evento VALUES(13, 'evento 126', 12, 'UNI');

INSERT INTO eventos.evento VALUES(14, 'evento 96', NULL, 'WAR');
INSERT INTO eventos.evento VALUES(15, 'evento 64', NULL, 'WAR');

INSERT INTO eventos.evento VALUES(16, 'evento 96', NULL, 'WAR');

INSERT INTO eventos.evento VALUES(17, 'evento 96', NULL, 'WAR');

INSERT INTO eventos.evento VALUES(18, 'evento 65', NULL, 'WAR');

INSERT INTO eventos.evento VALUES(19, 'evento 50', NULL, 'COL');

INSERT INTO eventos.evento VALUES(20, 'evento 9', NULL, 'WAR');
INSERT INTO eventos.evento VALUES(21, 'evento 21',  NULL, 'COL');
INSERT INTO eventos.evento VALUES(22, 'evento 22',  NULL, 'COL');

INSERT INTO eventos.evento VALUES(23, 'evento 23',  17, 'COL');

INSERT INTO eventos.evento VALUES(24, 'evento 24',  19, 'COL');

INSERT INTO eventos.evento VALUES(25, 'evento 25',  2, 'FOX');
INSERT INTO eventos.evento VALUES(26, 'evento 26',  NULL,'FOX');
INSERT INTO eventos.evento VALUES(27, 'evento 27', NULL,'COL');


INSERT INTO eventos.organizacao VALUES (1,'D100');
INSERT INTO eventos.organizacao VALUES (2,'D100');
INSERT INTO eventos.organizacao VALUES (3,'D100');
INSERT INTO eventos.organizacao VALUES (4,'D200');
INSERT INTO eventos.organizacao VALUES (5,'D200');
INSERT INTO eventos.organizacao VALUES (6,'D300');
INSERT INTO eventos.organizacao VALUES (7,'D300');
INSERT INTO eventos.organizacao VALUES (8,'D300');
INSERT INTO eventos.organizacao VALUES (9,'D400');
INSERT INTO eventos.organizacao VALUES (10,'D400');
INSERT INTO eventos.organizacao VALUES (11,'D400');
INSERT INTO eventos.organizacao VALUES (12,'D500');
INSERT INTO eventos.organizacao VALUES (13,'D500');
INSERT INTO eventos.organizacao VALUES (14,'D600');
INSERT INTO eventos.organizacao VALUES (15,'D600');
INSERT INTO eventos.organizacao VALUES (16,'D900');
INSERT INTO eventos.organizacao VALUES (17,'D1301');
INSERT INTO eventos.organizacao VALUES (18,'D1201');
INSERT INTO eventos.organizacao VALUES (19,'D700');
INSERT INTO eventos.organizacao VALUES (20,'D1501');
INSERT INTO eventos.organizacao VALUES (21,'D1501');
INSERT INTO eventos.organizacao VALUES (22,'D100');

INSERT INTO eventos.ingresso VALUES('C112', 7,40);
INSERT INTO eventos.ingresso VALUES('C102', 7,100);
INSERT INTO eventos.ingresso VALUES('C104', 7,78);
INSERT INTO eventos.ingresso VALUES('C109', 7,800);

INSERT INTO eventos.ingresso VALUES('C112', 8,55);
INSERT INTO eventos.ingresso VALUES('C102', 8,101);
INSERT INTO eventos.ingresso VALUES('C107', 8.9);
INSERT INTO eventos.ingresso VALUES('C108', 8,888.5);
INSERT INTO eventos.ingresso VALUES('C109', 8,100);

INSERT INTO eventos.ingresso VALUES('C104',5,813.7);
INSERT INTO eventos.ingresso VALUES('C109',5,NULL);
INSERT INTO eventos.ingresso VALUES('C110',20,5645.5);
INSERT INTO eventos.ingresso VALUES('C111',20,10.0);

INSERT INTO eventos.ingresso VALUES('C101', 2,1000.0);
INSERT INTO eventos.ingresso VALUES('C107', 2,1000.0);
INSERT INTO eventos.ingresso VALUES('C106', 2,1000.0);
INSERT INTO eventos.ingresso VALUES('C104', 2,1000.0);
INSERT INTO eventos.ingresso VALUES('C105', 2,1000.0);

INSERT INTO eventos.ingresso VALUES('C101',22,NULL);
INSERT INTO eventos.ingresso VALUES('C111',22,NULL);
INSERT INTO eventos.ingresso VALUES('C106',22,99.5);
INSERT INTO eventos.ingresso VALUES('C108',22,99.5);
INSERT INTO eventos.ingresso VALUES('C109',22,98.5);
INSERT INTO eventos.ingresso VALUES('C110',22,8123.1);

INSERT INTO eventos.ingresso VALUES('C112',6, NULL);
INSERT INTO eventos.ingresso VALUES('C102',6,NULL);
INSERT INTO eventos.ingresso VALUES('C104',6,NULL);
INSERT INTO eventos.ingresso VALUES('C106',6,NULL);
INSERT INTO eventos.ingresso VALUES('C107',6,NULL);
INSERT INTO eventos.ingresso VALUES('C108',21,NULL);
INSERT INTO eventos.ingresso VALUES('C109',21,NULL);
INSERT INTO eventos.ingresso VALUES('C111',21,NULL);

INSERT INTO eventos.ingresso VALUES('C106',9,NULL);
INSERT INTO eventos.ingresso VALUES('C110',9,NULL);
INSERT INTO eventos.ingresso VALUES('C111',9,NULL);
INSERT INTO eventos.ingresso VALUES('C108',9,NULL);

INSERT INTO eventos.ingresso VALUES('C108',11,NULL);
INSERT INTO eventos.ingresso VALUES('C107',11,NULL);
INSERT INTO eventos.ingresso VALUES('C110',11, NULL);


INSERT INTO eventos.ingresso VALUES('C101',12,98.5);
INSERT INTO eventos.ingresso VALUES('C111',12,777.6);
INSERT INTO eventos.ingresso VALUES('C110',12,777.7);

INSERT INTO eventos.ingresso VALUES('C106',3,978.0);
INSERT INTO eventos.ingresso VALUES('C110',3,NULL);
INSERT INTO eventos.ingresso VALUES('C101',3,745.0);
INSERT INTO eventos.ingresso VALUES('C112',3, 333);
INSERT INTO eventos.ingresso VALUES('C107',3,312.2);

INSERT INTO eventos.ingresso VALUES('C101',13,822.0);
INSERT INTO eventos.ingresso VALUES('C111',13,822.0);
INSERT INTO eventos.ingresso VALUES('C109',13,478.0);

INSERT INTO eventos.ingresso VALUES('C101', 15,4.0);
INSERT INTO eventos.ingresso VALUES('C111', 15,3.5);
INSERT INTO eventos.ingresso VALUES('C107', 15,2.0);
INSERT INTO eventos.ingresso VALUES('C102', 15,8.0);
INSERT INTO eventos.ingresso VALUES('C112', 15,6.0);

INSERT INTO eventos.ingresso VALUES('C106', 18,654.0);
INSERT INTO eventos.ingresso VALUES('C111', 18,745.5);
INSERT INTO eventos.ingresso VALUES('C109', 18,67878.0);
INSERT INTO eventos.ingresso VALUES('C110', 18,978.0);

INSERT INTO eventos.ingresso VALUES('C102', 14,798);
INSERT INTO eventos.ingresso VALUES('C104', 14,611.0);
INSERT INTO eventos.ingresso VALUES('C106', 16,10111.0);
INSERT INTO eventos.ingresso VALUES('C107', 16,0.0);
INSERT INTO eventos.ingresso VALUES('C108', 16,9.0);
INSERT INTO eventos.ingresso VALUES('C110', 17, 8.5);

INSERT INTO eventos.ingresso VALUES('C101',23,8.0);
INSERT INTO eventos.ingresso VALUES('C105',23,8.0);
INSERT INTO eventos.ingresso VALUES('C109',23,4.0);

INSERT INTO eventos.ingresso VALUES('C101', 24,4.0);
INSERT INTO eventos.ingresso VALUES('C110', 24,3.5);
INSERT INTO eventos.ingresso VALUES('C107', 24,2.0);
INSERT INTO eventos.ingresso VALUES('C102', 24,7.0);
INSERT INTO eventos.ingresso VALUES('C111', 24,6.0);

INSERT INTO eventos.ingresso VALUES('C106', 25,6.0);
INSERT INTO eventos.ingresso VALUES('C111', 25,7.5);
INSERT INTO eventos.ingresso VALUES('C109', 25,6.0);
INSERT INTO eventos.ingresso VALUES('C112', 25,580.0);
