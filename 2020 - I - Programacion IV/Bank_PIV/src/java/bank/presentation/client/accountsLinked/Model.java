package bank.presentation.client.accountsLinked;

import bank.logic.Cuenta;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Model {
    
    private List<Cuenta> accountsLinked;
    private Cuenta accountToLink;
    
    public Model(){
        this.accountsLinked = new ArrayList<>();
        accountToLink = null;
    }

    public Cuenta getAccountToLink() {
        return accountToLink;
    }

    public void setAccountToLink(Cuenta accountToLink) {
        this.accountToLink = accountToLink;
    }

    public List<Cuenta> getAccountsLinked() {
        return accountsLinked;
    }

    public void setAccountsLinked(List<Cuenta> accounts) {
        this.accountsLinked = accounts;
    }
    
}