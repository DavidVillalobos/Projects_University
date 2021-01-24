package bank.presentation.client.accounts;

import bank.logic.Cuenta;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Model {
    
    private List<Cuenta> accounts;
    
    public Model(){
        this.accounts = new ArrayList<>();
    }
    
    public List<Cuenta> getAccounts() {
        return accounts;
    }

    public void setAccounts(List<Cuenta> accounts) {
        this.accounts = accounts;
    }
    
}
