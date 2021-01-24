/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
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
import javax.validation.constraints.Size;

/**
 *
 * @author Home
 */
@Entity
@Table(name = "dishes")
@NamedQueries({
    @NamedQuery(name = "Dishes.findAll", query = "SELECT d FROM Dishes d")})
public class Dishes implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 45)
    @Column(name = "name")
    private String name;
    @Basic(optional = false)
    @NotNull
    @Column(name = "price")
    private double price;
    @Size(max = 300)
    @Column(name = "decription")
    private String decription;
    @JoinColumn(name = "categorie", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Categories categories;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "dishes")
    private List<ClientDish> clientDishList;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "dishes")
    private List<Additionals> additionalsList;

    public Dishes() {
        this.id=0;
    }

    public Dishes(Integer id) {
        this.id = id;
    }

    public Dishes(Integer id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public String getDecription() {
        return decription;
    }

    public void setDecription(String decription) {
        this.decription = decription;
    }

    public Categories getCategories() {
        return categories;
    }

    public void setCategories(Categories categories) {
        this.categories = categories;
    }

    public List<ClientDish> getClientDishList() {
        return clientDishList;
    }

    public void setClientDishList(List<ClientDish> clientDishList) {
        this.clientDishList = clientDishList;
    }

    public List<Additionals> getAdditionalsList() {
        return additionalsList;
    }

    public void setAdditionalsList(List<Additionals> additionalsList) {
        this.additionalsList = additionalsList;
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
        if (!(object instanceof Dishes)) {
            return false;
        }
        Dishes other = (Dishes) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "food_service.logic.Dishes[ id=" + id + " ]";
    }
    
}
