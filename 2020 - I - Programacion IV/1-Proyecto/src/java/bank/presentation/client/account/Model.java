package bank.presentation.client.account;

import bank.logic.Cuenta;
import bank.logic.Movimiento;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Model {
    
    private Cuenta account;
    private List<Movimiento> movements;

    public Model() {
        account = new Cuenta();
        movements = new ArrayList<>();
    }

    public List<Movimiento> getMovements() {
        return movements;
    }

    public void setMovements(List<Movimiento> movements) {
        this.movements = movements;
    }
    
    public Cuenta getAccount() {
        return account;
    }

    public void setAccount(Cuenta account) {
        this.account = account;
    }

}
