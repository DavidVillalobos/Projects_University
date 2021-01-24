/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bank.logic;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author Kevin Flores
 */
@Entity
@Table(name = "vinculo")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Vinculo.findAll", query = "SELECT v FROM Vinculo v")
    , @NamedQuery(name = "Vinculo.findByIdVinculo", query = "SELECT v FROM Vinculo v WHERE v.idVinculo = :idVinculo")})
public class Vinculo implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "idVinculo")
    private Integer idVinculo;
    @JoinColumn(name = "cliente", referencedColumnName = "cedula")
    @ManyToOne(optional = false)
    private Cliente cliente;
    @JoinColumn(name = "cuenta", referencedColumnName = "idCuenta")
    @ManyToOne(optional = false)
    private Cuenta cuenta;

    public Vinculo() {
    }

    public Vinculo(Integer idVinculo) {
        this.idVinculo = idVinculo;
    }

    public Integer getIdVinculo() {
        return idVinculo;
    }

    public void setIdVinculo(Integer idVinculo) {
        this.idVinculo = idVinculo;
    }

    public Cliente getCliente() {
        return cliente;
    }

    public void setCliente(Cliente cliente) {
        this.cliente = cliente;
    }

    public Cuenta getCuenta() {
        return cuenta;
    }

    public void setCuenta(Cuenta cuenta) {
        this.cuenta = cuenta;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idVinculo != null ? idVinculo.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Vinculo)) {
            return false;
        }
        Vinculo other = (Vinculo) object;
        if ((this.idVinculo == null && other.idVinculo != null) || (this.idVinculo != null && !this.idVinculo.equals(other.idVinculo))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "bank.logic.Vinculo[ idVinculo=" + idVinculo + " ]";
    }
    
}
