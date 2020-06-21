package com.food_service.logic;
import com.food_service.data.*;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 *
 * @author David Villalobos
 */

public class Model {
    private static Model uniqueInstance;
    private final Dao_Additionals adicionales;
    private final Dao_Administrator_Status estados_administrador;
    private final Dao_Administrators administradores;
    private final Dao_Adresses direcciones;
    private final Dao_Categories categorias;
    private final Dao_Client_Dish platillos_cliente;
    private final Dao_Cliente_Additionals adicionales_cliente;
    private final Dao_Cliente_Details detalles_cliente;
    private final Dao_Clients clientes;
    private final Dao_Details detalles;
    private final Dao_Dishes platillos;
    private final Dao_Locations ubicaciones;
    private final Dao_Order_Status estados_orden;
    private final Dao_Orders ordenes;
    
    public static Model instance(){
        if (uniqueInstance == null){
            uniqueInstance = new Model();
        }
        return uniqueInstance; 
    }

    private Model(){
        adicionales = Dao_Additionals.instance();
        estados_administrador = Dao_Administrator_Status.instance();
        administradores = Dao_Administrators.instance();
        direcciones = Dao_Adresses.instance();
        categorias = Dao_Categories.instance();
        platillos_cliente = Dao_Client_Dish.instance();
        adicionales_cliente = Dao_Cliente_Additionals.instance();
        detalles_cliente = Dao_Cliente_Details.instance();
        clientes = Dao_Clients.instance();
        detalles = Dao_Details.instance();
        platillos = Dao_Dishes.instance();
        ubicaciones = Dao_Locations.instance();
        estados_orden = Dao_Order_Status.instance();
        ordenes = Dao_Orders.instance();
    }
    
    //----------------------Utiles--------------------------------//
    public void setSchedule(String date, Orders globalOrder) throws ParseException{
        if(date.equals("asap")){
            globalOrder.setAsap(Short.parseShort("1"));
            globalOrder.setDeliveryDate(null);
        }
        else{
            String date_ = date.replace('T',' ');
            SimpleDateFormat formatter =new SimpleDateFormat("yyyy-MM-dd HH:mm");
            Date nueva = formatter.parse(date_);
            globalOrder.setAsap(Short.parseShort("0"));
            globalOrder.setDeliveryDate(nueva);
        }
    }
    
    public Boolean hasAdditionals(String idDish) throws SQLException{
        return !adicionales.getByDish(idDish).isEmpty();
    }
    
    public Double calculateTotalOrder(Orders or){
        Double total = 0.0;
        for(ClientDish d:or.getClientDishList()){
            total+=d.getTotal();
        }
        return total;
    }
    
    public Clients getLast() throws Exception{
        return clientes.getLast();
    }
    
    public Orders getLastOrder() throws Exception{
        return ordenes.getLast();
    }
    
    public String getRandomString() {
        String key = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        int length = 10;
        String pswd = "";
        for (int i = 0; i < length; i++) {
            pswd+=(key.charAt((int)(Math.random() * key.length())));
        }
        return pswd;
    }
    
    public void deleteFromOrder(String index, Orders order){
        int index_ = Integer.parseInt(index);
        if(index_<order.getClientDishList().size()){
            order.getClientDishList().remove(index_);
        }
    }
    
    public Double calculateTotalDish(ClientDish d){
        Double t=d.getDishes().getPrice();
        if(d.getClienteAdditionalsList() != null){
        for(ClienteAdditionals cd:d.getClienteAdditionalsList()){
            for(ClienteDetails cdetails:cd.getClienteDetailsList()){
                t+=cdetails.getDetails().getPrice();
            }
        }
        }
        t*=d.getQuantity();
        return t;
    }
    
    public void addDishToOrder(Orders globalOrder, ClientDish dish, Boolean addi){
        Boolean oldDish=false;
        if(!addi){
            for(ClientDish d:globalOrder.getClientDishList()){
                if(d.getDishes().getId().equals(dish.getDishes().getId())){
                    d.setQuantity(d.getQuantity()+dish.getQuantity());
                    d.setTotal(this.calculateTotalDish(d));
                    oldDish=true; break;
                }
            }
            if(!oldDish){
                dish.setTotal(this.calculateTotalDish(dish));
                globalOrder.getClientDishList().add(dish);
                return; 
            }
            return;
        }   
        for(ClientDish d:globalOrder.getClientDishList()){
            if(sameDishes(d,dish)){
                d.setQuantity(d.getQuantity()+dish.getQuantity());
                d.setTotal(this.calculateTotalDish(d));
                oldDish=true;
                break;
            } 
        }
        if(!oldDish){
            dish.setTotal(this.calculateTotalDish(dish));
            globalOrder.getClientDishList().add(dish);
        }
    }
    
    public Boolean sameDishes(ClientDish d1, ClientDish d2){
        
        //Son del mismo Dish
        if(!d1.getDishes().getId().equals(d2.getDishes().getId())) return false;
        
        //Tiene los mismos detalles
        Boolean isIn;
        for(ClienteAdditionals ca1 : d1.getClienteAdditionalsList()){
            for(ClienteAdditionals ca2 : d2.getClienteAdditionalsList()){
                if(ca1.getAdditionals().getId().equals(ca2.getAdditionals().getId())){
                    if(ca2.getClienteDetailsList().size() != ca1.getClienteDetailsList().size())
                        return false;
                    for(ClienteDetails cd1 : ca1.getClienteDetailsList()){
                        isIn=false;
                        for(ClienteDetails cd2 : ca2.getClienteDetailsList()){
                            
                            if(cd1.getDetails().getId().equals(cd2.getDetails().getId())){
                                isIn=true;
                                break;
                            }
                        }
                        if(!isIn) return false;
                    }
                }
            }
        }
        return true;
    }


    //----------------------Agregar datos-------------------------//
    
    public void adicionalesAdd(Additionals p) throws Exception {
        adicionales.add(p);
    }
    
    public void estadosAdministradorAdd(AdministratorStatus p) throws Exception {
        estados_administrador.add(p);
    }
    
    public void administradorAdd(Administrators p) throws Exception {
        administradores.add(p);
    }
    
    public void direccionesAdd(Adresses p) throws Exception {
        direcciones.add(p);
    }
    
    public void categoriasAdd(Categories p) throws Exception {
        categorias.add(p);
    }
    
    public void platillosClienteAdd(ClientDish p) throws Exception {
        platillos_cliente.add(p);
    }
    
    public void adicionalesClienteAdd(ClienteAdditionals p) throws Exception {
        adicionales_cliente.add(p);
    }
    
    public void detallesClienteAdd(ClienteDetails p) throws Exception {
        detalles_cliente.add(p);
    }
    
    public void clienteAdd(Clients p) throws Exception {
        clientes.add(p);
    }
    
    public void detallesAdd(Details p) throws Exception {
        detalles.add(p);
    }
    
    public void platillosAdd(Dishes p) throws Exception {
        platillos.add(p);
    }
    
    public void ubicacionesAdd(Locations p) throws Exception {
        ubicaciones.add(p);
    }
    
    public void estadosOrdenAdd(OrderStatus p) throws Exception {
        estados_orden.add(p);
    }
    
    public void ordenesAdd(Orders p) throws Exception {
        ordenes.add(p);
    }
    
    //----------------------Busquedas----------------------------//
    
    // Por ID
    public Additionals adicionalesget(int id) throws Exception {
        return adicionales.get(id);
    }
    
    public List<Additionals> adicionalesByDish(String idDish) throws SQLException{
        return adicionales.getByDish(idDish);
    }
    
    public List<Details> detallesByAdditional(Integer idAdditional) throws SQLException{
        return detalles.getByAdditional(idAdditional);
    }
    
    public AdministratorStatus estadosAdministradorget(int id) throws Exception {
        return estados_administrador.get(id);
    }
    
    public Administrators administradorget(int id ) throws Exception {
        return administradores.get(id);
    }
    
    public Administrators administradorgetByUserName(String userName) throws Exception {
        return administradores.getbyUserName(userName);
    }
    
    public Adresses direccionesget(int id) throws Exception {
        return direcciones.get(id);
    }
    
    public Categories categoriasget(int id) throws Exception {
        return categorias.get(id);
    }
    
    public ClientDish platillosClienteget(int id) throws Exception {
        return platillos_cliente.get(id);
    }
    
    public ClienteAdditionals adicionalesClienteget(int id) throws Exception {
        return adicionales_cliente.get(id);
    }
    
    public ClienteDetails detallesClienteget(int id) throws Exception {
        return detalles_cliente.get(id);
    }
    
    public Clients clienteget(int id) throws Exception {
       return clientes.getById(id);
    }
     
    public Clients clientegetByEmail(String email) throws Exception {
        return clientes.get(email);
    }
    
    public Details detallesget(int id) throws Exception {
        return detalles.get(id);
    }
    
    public Dishes platillosget(int id) throws Exception {
        return platillos.get(id);
    }
    
    public List<Dishes> platilloByCategoria(String idCategoria) throws SQLException{
        return platillos.getByCategorie(idCategoria);
    }
    
    public Locations ubicacionesget(int id) throws Exception {
        return ubicaciones.get(id);
    }
    
    public OrderStatus estadosOrdenget(int id) throws Exception {
        return estados_orden.get(id);
    }
    
    public Orders ordenesget(int id) throws Exception {
        return ordenes.get(id);
    }
    
    //   Todos
    
    public List<Additionals> adicionalesgetAll() throws Exception {
        return adicionales.getAll();
    }
    
    public List<AdministratorStatus> estadosAdministradorgetAll() throws Exception {
        return estados_administrador.getAll();
    }
    
    public List<Administrators> administradorgetAll( ) throws Exception {
        return administradores.getAll();
    }
    
    public List<Adresses> direccionesgetAll() throws Exception {
        return direcciones.getAll();
    }
    
    public List<Categories> categoriasgetAll() throws Exception {
        return categorias.getAll();
    }
    
    public List<ClientDish> platillosClientegetAll() throws Exception {
        return platillos_cliente.getAll();
    }
    
    public List<ClienteAdditionals> adicionalesClientegetAll() throws Exception {
        return adicionales_cliente.getAll();
    }
    
    public List<ClienteDetails> detallesClientegetAll() throws Exception {
        return detalles_cliente.getAll();
    }
    
    public List<Clients> clientegetAll() throws Exception {
       return clientes.getAll();
    }
    
    public List<Details> detallesgetAll() throws Exception {
        return detalles.getAll();
    }
    
    public List<Dishes> platillosgetAll() throws Exception {
        return platillos.getAll();
    }
    
    public List<Locations> ubicacionesgetAll() throws Exception {
        return ubicaciones.getAll();
    }
    
    public List<OrderStatus> estadosOrdengetAll() throws Exception {
        return estados_orden.getAll();
    }
    
    public List<Orders> ordenesgetAll() throws Exception {
        return ordenes.getAll();
    }
    
    //----------------------Actualizaciones-----------------------//
    
    public void adicionalesUpdate(Additionals p) throws Exception {
        adicionales.update(p);
    }
    
    public void estadosAdministradorUpdate(AdministratorStatus p) throws Exception {
        estados_administrador.update(p);
    }
    
    public void administradorUpdate(Administrators p) throws Exception {
        administradores.update(p);
    }
    
    public void direccionesUpdate(Adresses p) throws Exception {
        direcciones.update(p);
    }
    
    public void categoriasUpdate(Categories p) throws Exception {
        categorias.update(p);
    }
    
    public void platillosClienteUpdate(ClientDish p) throws Exception {
        platillos_cliente.update(p);
    }
    
    public void adicionalesClienteUpdate(ClienteAdditionals p) throws Exception {
        adicionales_cliente.update(p);
    }
    
    public void detallesClienteUpdate(ClienteDetails p) throws Exception {
        detalles_cliente.update(p);
    }
    
    public void clienteUpdate(Clients p) throws Exception {
        clientes.update(p);
    }
    
    public void detallesUpdate(Details p) throws Exception {
        detalles.update(p);
    }
    
    public void platillosUpdate(Dishes p) throws Exception {
        platillos.update(p);
    }
    
    public void ubicacionesUpdate(Locations p) throws Exception {
        ubicaciones.update(p);
    }
    
    public void estadosOrdenUpdate(OrderStatus p) throws Exception {
        estados_orden.update(p);
    }
    
    public void ordenesUpdate(Orders p) throws Exception {
        ordenes.update(p);
    }
    
    //----------------------Eliminaciones-----------------------//
    
    public void adicionalesdelete(int id) throws Exception {
        adicionales.delete(id);
    }
    
    public void estadosAdministradordelete(int id) throws Exception {
        estados_administrador.delete(id);
    }
    
    public void administradordelete(int id ) throws Exception {
        administradores.delete(id);
    }
    
    public void direccionesdelete(int id) throws Exception {
        direcciones.delete(id);
    }
    
    public void categoriasdelete(int id) throws Exception {
        categorias.delete(id);
    }
    
    public void platillosClientedelete(int id) throws Exception {
        platillos_cliente.delete(id);
    }
    
    public void adicionalesClientedelete(int id) throws Exception {
        adicionales_cliente.delete(id);
    }
    
    public void detallesClientedelete(int id) throws Exception {
        detalles_cliente.delete(id);
    }
    
    public void clientedelete(int id) throws Exception {
       clientes.delete(id);
    }
    
    public void detallesdelete(int id) throws Exception {
       detalles.delete(id);
    }
    
    public void platillosdelete(int id) throws Exception {
       platillos.delete(id);
    }
    
    public void ubicacionesdelete(int id) throws Exception {
       ubicaciones.delete(id);
    }
    
    public void estadosOrdendelete(int id) throws Exception {
       estados_orden.delete(id);
    }
    
    public void ordenesdelete(int id) throws Exception {
       ordenes.delete(id);
    }
    
}
