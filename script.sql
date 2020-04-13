insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('CRC', 'Colon', 1, '1');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('USD', 'Dolar', 571.86, '2');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('EUR', 'Euro', 621.11, '3');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('MXN', 'Peso Mexicano', 23.42, '1');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('COP', 'Peso Colombiano', 0.14, '1');
insert into moneda(idMoneda, nombreMoneda, valorColones, interes) values ('CNY', 'Yuan Chino', 80.92 ,'3');

insert into tipomovimiento(idTipoMovimiento, nombre) values (1, 'Retiro');
insert into tipomovimiento(idTipoMovimiento, nombre) values (2, 'Deposito');

insert into usuario (idUsuario, password, tipo) values (333, 333, 1);

insert into cliente (cedula, nombre, telefono, usuario) values ('333', 'Juan Rodriguez', '333333', '333');

select * from cliente;
select * from cuenta;
select * from usuario;
select * from movimiento;
select * from tipomovimiento;
select * from vinculo;
select * from moneda;