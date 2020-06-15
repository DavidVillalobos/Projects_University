
package com.food_service.logic;

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

/**
 *
 * @author Home
 */
@Entity
@Table(name = "client_dish")
@NamedQueries({
    @NamedQuery(name = "ClientDish.findAll", query = "SELECT c FROM ClientDish c")})
public class ClientDish implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Column(name = "quantity")
    private int quantity;  //Got it
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "clientDish")
    private List<ClienteAdditionals> clienteAdditionalsList;
    @JoinColumn(name = "dish", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Dishes dishes; // Got it
    @JoinColumn(name = "order", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Orders orders; // Id needed

    public ClientDish() {
        
    }

    public ClientDish(Integer id) {
        this.id = id;
    }

    public ClientDish(Integer id, int quantity) {
        this.id = id;
        this.quantity = quantity;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public List<ClienteAdditionals> getClienteAdditionalsList() {
        return clienteAdditionalsList;
    }

    public void setClienteAdditionalsList(List<ClienteAdditionals> clienteAdditionalsList) {
        this.clienteAdditionalsList = clienteAdditionalsList;
    }

    public Dishes getDishes() {
        return dishes;
    }

    public void setDishes(Dishes dishes) {
        this.dishes = dishes;
    }

    public Orders getOrders() {
        return orders;
    }

    public void setOrders(Orders orders) {
        this.orders = orders;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof ClientDish)) {
            return false;
        }
        ClientDish other = (ClientDish) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "food_service.logic.ClientDish[ id=" + id + " ]";
    }
    
}
