--Desactivamos las verificaciones de las llaves foraneas
SET FOREIGN_KEY_CHECKS=0;
--Ahora podemos eliminar los registros de las tablas
TRUNCATE TABLE cliente;
TRUNCATE TABLE cuenta;
TRUNCATE TABLE moneda;
TRUNCATE TABLE movimiento;
TRUNCATE TABLE tipomovimiento;
TRUNCATE TABLE usuario;
TRUNCATE TABLE vinculo;
--Activamos las verificaciones de las llaves foraneas
SET FOREIGN_KEY_CHECKS=1;

-- Inserts en la tabla moneda
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('CRC', 'Colon', 1, '1');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('USD', 'Dolar', 560, '2');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('EUR', 'Euro', 610, '3');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('MXN', 'Peso Mexicano', 22, '1');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('CNY', 'Yuan Chino', 80, '3');

-- Inserts en la tabla tipomovimiento
insert into tipomovimiento(idTipoMovimiento, nombre) values (1, 'Retiro');
insert into tipomovimiento(idTipoMovimiento, nombre) values (2, 'Deposito');

-- Inserts de un cajero
insert into usuario (idUsuario, password, tipo) values (111, 111, 1);
insert into cliente (cedula, nombre, telefono, usuario) values ('111', 'Juan Rodriguez', '111', '111');

-- Visualizar las tablas
select * from cliente;
select * from cuenta;
select * from usuario;
select * from movimiento;
select * from tipomovimiento;
select * from vinculo;
select * from moneda;