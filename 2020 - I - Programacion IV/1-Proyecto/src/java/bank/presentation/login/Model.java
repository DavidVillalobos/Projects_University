package bank.presentation.login;

import bank.logic.Cliente;


/**
 *
 * @author Kevin Flores
 */
public class Model {
    
    private Cliente client;

    public Model() {
        this.client = new Cliente();
    }

    public Cliente getClient() {
        return client;
    }

    public void setClient(Cliente client) {
        this.client = client;
    }
    
   
}
