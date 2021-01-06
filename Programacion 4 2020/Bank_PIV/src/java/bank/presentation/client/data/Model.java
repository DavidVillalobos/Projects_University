package bank.presentation.client.data;

import bank.logic.Cliente;

/**
 *
 * @author David Villalobos
 */
public class Model {
    private Cliente client;

    public Model() {
        client = null;
    }
    
    public Cliente getClient() {
        return client;
    }

    public void setClient(Cliente cliente) {
        this.client = cliente;
    }
    
}