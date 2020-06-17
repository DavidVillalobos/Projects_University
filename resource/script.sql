-- Desactivamos las verificaciones de las llaves foraneas
SET FOREIGN_KEY_CHECKS=0;
-- Ahora podemos eliminar los registros de las tablas
TRUNCATE TABLE additionals;
TRUNCATE TABLE administrator_status;
TRUNCATE TABLE administrators;
TRUNCATE TABLE adresses;
TRUNCATE TABLE categories;
TRUNCATE TABLE client_dish;
TRUNCATE TABLE cliente_additionals;
TRUNCATE TABLE cliente_details;
TRUNCATE TABLE clients;
TRUNCATE TABLE details;
TRUNCATE TABLE dishes;
TRUNCATE TABLE locations;
TRUNCATE TABLE order_status;
TRUNCATE TABLE orders;
TRUNCATE TABLE cliente_additionals;
-- Activamos las verificaciones de las llaves foraneas
SET FOREIGN_KEY_CHECKS=1;
-- Insert Categories
insert into categories(name) values ('Aperitivo');
insert into categories(name) values ('Plato Principal');
insert into categories(name) values ('Ensaladas');
insert into categories(name) values ('Mariscos');
insert into categories(name) values ('Tradicional');
insert into categories(name) values ('Vegetariano');
insert into categories(name) values ('Sopas');
insert into categories(name) values ('Postres');
insert into categories(name) values ('Bebidas');
insert into categories(name) values ('Especiales');
insert into categories(name) values ('Platos de arroz');

-- Insert Dishes

-- Insert Administrator Status
insert into administrator_status(name) values ('Vuelvo pronto');
insert into administrator_status(name) values ('Conectado');
insert into administrator_status(name) values ('Desconectado');

-- Insert Administrator
insert into administrators(user_name, password, name, email, administrator_status) values ('admin1', 'admin1', 'Juan', 'juan@gmail.com', 2);
insert into administrators(user_name, password, name, email, administrator_status) values ('admin2', 'admin2', 'Maria', 'maria@gmail.com', 1);

-- Insert Locations
insert into locations (name, administrator) values ('The Healthy Grill', 1);
insert into locations (name, administrator) values ('The Ambrosia', 2);

-- Insert Dishes
insert into dishes(name,price,decription,categorie)
values("Sopita de Cangrejo", 15000, "Sopa Pequeña, con fresco incluido y el cangrejo de agua salada.", 4);
insert into dishes(name,price,decription,categorie) 
values("Ensalda Fria", 9000, "Contiene: caracoles, mayonesa, atun...con fresco incluido y doble porcion gratis.", 3); 
insert into dishes(name,price,decription,categorie)
values("Ensalada Coloria", 15000, "Ensalada Grande, contiene: zanahoria, lechuga, apio, tomate, pepino.", 3); 

-- Insert Additionals
insert into additionals(name,type,mandatory,dish) values("Salsas",true,true,3);
insert into additionals(name,type,mandatory,dish) values("Queso",false,false,3);

-- Insert Details
insert into details(name,price,additional) values("Mayonesa",500,1);
insert into details(name,price,additional) values("Limon Dulce",600,1);
insert into details(name,price,additional) values("Rosada",550,1); 

insert into details(name,price,additional) values("Amarillo",200,2);
insert into details(name,price,additional) values("Parmesano",300,2);


-- select * from additionals;
select * from administrator_status;
select * from administrators;
-- select * from adresses;
select * from categories;
-- select * from client_dish;
-- select * from cliente_additionals;
-- select * from cliente_details;
-- select * from clients;
-- select * from details;
select * from dishes;
select * from locations;
-- select * from order_status;
-- select * from orders;
-- select * from client_additionals

