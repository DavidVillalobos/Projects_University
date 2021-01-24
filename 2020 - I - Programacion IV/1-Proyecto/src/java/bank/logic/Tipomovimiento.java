/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bank.logic;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author Kevin Flores
 */
@Entity
@Table(name = "tipomovimiento")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Tipomovimiento.findAll", query = "SELECT t FROM Tipomovimiento t")
    , @NamedQuery(name = "Tipomovimiento.findByIdTipoMovimiento", query = "SELECT t FROM Tipomovimiento t WHERE t.idTipoMovimiento = :idTipoMovimiento")
    , @NamedQuery(name = "Tipomovimiento.findByNombre", query = "SELECT t FROM Tipomovimiento t WHERE t.nombre = :nombre")})
public class Tipomovimiento implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "idTipoMovimiento")
    private Integer idTipoMovimiento;
    @Size(max = 20)
    @Column(name = "nombre")
    private String nombre;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tipo")
    private List<Movimiento> movimientoList;

    public Tipomovimiento() {
    }

    public Tipomovimiento(Integer idTipoMovimiento) {
        this.idTipoMovimiento = idTipoMovimiento;
    }

    public Integer getIdTipoMovimiento() {
        return idTipoMovimiento;
    }

    public void setIdTipoMovimiento(Integer idTipoMovimiento) {
        this.idTipoMovimiento = idTipoMovimiento;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    @XmlTransient
    public List<Movimiento> getMovimientoList() {
        return movimientoList;
    }

    public void setMovimientoList(List<Movimiento> movimientoList) {
        this.movimientoList = movimientoList;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idTipoMovimiento != null ? idTipoMovimiento.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Tipomovimiento)) {
            return false;
        }
        Tipomovimiento other = (Tipomovimiento) object;
        if ((this.idTipoMovimiento == null && other.idTipoMovimiento != null) || (this.idTipoMovimiento != null && !this.idTipoMovimiento.equals(other.idTipoMovimiento))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "bank.logic.Tipomovimiento[ idTipoMovimiento=" + idTipoMovimiento + " ]";
    }
    
}
