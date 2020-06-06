package food_service.logic;
import food_service.data.Dao_Clients;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;


/**
 *
 * @author David Villalobos
 */
public class Model {
    private static Model uniqueInstance;
    private final Dao_Clients clientes;
    
    public static Model instance(){
        if (uniqueInstance == null){
            uniqueInstance = new Model();
        }
        return uniqueInstance; 
    }

    private Model(){
        clientes = Dao_Clients.instance();
    }

    //----------------------Insertar datos-------------------------//
    
   
    //----------------------Busquedas----------------------------//
    
   
   
    //----------------------Verificaciones-------------------------//
    
    
    
    //----------------------Actualizaciones-----------------------//
    
  
    //--------------------------------------------------------------//

}
