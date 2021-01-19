package bank.logic;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author Kevin Flores
 */
@Entity
@Table(name = "cuenta")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Cuenta.findAll", query = "SELECT c FROM Cuenta c")
    , @NamedQuery(name = "Cuenta.findByIdCuenta", query = "SELECT c FROM Cuenta c WHERE c.idCuenta = :idCuenta")
    , @NamedQuery(name = "Cuenta.findBySaldo", query = "SELECT c FROM Cuenta c WHERE c.saldo = :saldo")
    , @NamedQuery(name = "Cuenta.findByLimite", query = "SELECT c FROM Cuenta c WHERE c.limite = :limite")})
public class Cuenta implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "idCuenta")
    private Integer idCuenta;
    @Basic(optional = false)
    @NotNull
    @Column(name = "saldo")
    private double saldo;
    @Basic(optional = false)
    @NotNull
    @Column(name = "limite")
    private double limite;
    @OneToMany(mappedBy = "cuentaOrigen")
    private List<Movimiento> movimientoList;
    @OneToMany(mappedBy = "cuentaDestino")
    private List<Movimiento> movimientoList1;
    @JoinColumn(name = "cliente", referencedColumnName = "cedula")
    @ManyToOne(optional = false)
    private Cliente cliente;
    @JoinColumn(name = "moneda", referencedColumnName = "idMoneda")
    @ManyToOne(optional = false)
    private Moneda moneda;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "cuenta")
    private List<Vinculo> vinculoList;

    public Cuenta() {
        
    }

    public Cuenta(Integer idCuenta) {
        this.idCuenta = idCuenta;
    }

    public Cuenta(Integer idCuenta, double saldo, double limite) {
        this.idCuenta = idCuenta;
        this.saldo = saldo;
        this.limite = limite;
    }
    
    public Cuenta(Integer idCuenta, double saldo, Cliente client) {
        this.idCuenta = idCuenta;
        this.saldo = saldo;
        this.cliente = client;
    }

    public Integer getIdCuenta() {
        return idCuenta;
    }

    public void setIdCuenta(Integer idCuenta) {
        this.idCuenta = idCuenta;
    }

    public double getSaldo() {
        return saldo;
    }

    public void setSaldo(double saldo) {
        this.saldo = saldo;
    }

    public double getLimite() {
        return limite;
    }

    public void setLimite(double limite) {
        this.limite = limite;
    }

    @XmlTransient
    public List<Movimiento> getMovimientoList() {
        return movimientoList;
    }

    public void setMovimientoList(List<Movimiento> movimientoList) {
        this.movimientoList = movimientoList;
    }

    @XmlTransient
    public List<Movimiento> getMovimientoList1() {
        return movimientoList1;
    }

    public void setMovimientoList1(List<Movimiento> movimientoList1) {
        this.movimientoList1 = movimientoList1;
    }

    public Cliente getCliente() {
        return cliente;
    }

    public void setCliente(Cliente cliente) {
        this.cliente = cliente;
    }

    public Moneda getMoneda() {
        return moneda;
    }

    public void setMoneda(Moneda moneda) {
        this.moneda = moneda;
    }

    @XmlTransient
    public List<Vinculo> getVinculoList() {
        return vinculoList;
    }

    public void setVinculoList(List<Vinculo> vinculoList) {
        this.vinculoList = vinculoList;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idCuenta != null ? idCuenta.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Cuenta)) {
            return false;
        }
        Cuenta other = (Cuenta) object;
        if ((this.idCuenta == null && other.idCuenta != null) || (this.idCuenta != null && !this.idCuenta.equals(other.idCuenta))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "bank.logic.Cuenta[ idCuenta=" + idCuenta + " ]";
    }
    
}
