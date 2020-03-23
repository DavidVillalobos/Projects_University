package bank.presentation.login;

import bank.logic.Usuario;

/**
 *
 * @author Kevin Flores
 */
public class Model {
    
    private Usuario user;
    
    public Model(){
        this.user = new Usuario();
    }

    public Usuario getUser() {
        return user;
    }

    public void setUser(Usuario user) {
        this.user = user;
    }
    
}
