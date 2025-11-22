package es.upm.Controladora;

import es.upm.Modelo.*;
import es.upm.Vista.IVistas.IVistaMascota;
import es.upm.Vista.IVistas.IVistaResponsable;
import es.upm.Vista.VColores;
import es.upm.Vista.VMascota;
import es.upm.Vista.VResponsable;
import servidor.ExternalRRSS;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class CResponsable {
    private IVistaResponsable vistaResponsable;
    private IVistaMascota vistaMascota;
    private List<Responsable> listaresponsable;
    private CCuidador hermana;

    public IVistaResponsable getVistaResponsable() {
        return vistaResponsable;
    }

    public void setVistaResponsable(IVistaResponsable vistaResponsable) {
        this.vistaResponsable = vistaResponsable;
    }

    public IVistaMascota getVistaMascota() {
        return vistaMascota;
    }

    public void setVistaMascota(IVistaMascota vistaMascota) {
        this.vistaMascota = vistaMascota;
    }

    public List<Responsable> getListaresponsable() {
        return listaresponsable;
    }

    public void setListaresponsable(List<Responsable> listaresponsable) {
        this.listaresponsable = listaresponsable;
    }

    public CCuidador getHermana() {
        return hermana;
    }

    public void setHermana(CCuidador hermana) {
        this.hermana = hermana;
    }

    public CResponsable(CCuidador hermana) {
        listaresponsable = new LinkedList<>();
        this.hermana = hermana;
        this.vistaResponsable = new VResponsable();
        this.vistaMascota = new VMascota();
    }

    public void listarMascotas(Usuario logueado) {
        if (!(logueado instanceof Responsable)) {
            System.out.println(VColores.ROSA+"El usuario no es un responsable."+VColores.RESET);
        } else {
            List<Mascota> mascotas = logueado.getMascotas();
            if (mascotas.isEmpty()) {
                System.out.println(VColores.PURPLE +"No tienes mascotas."+VColores.RESET);
            }else{
                System.out.println(VColores.ROSA + "Tus mascotas: " + VColores.RESET);
                for (Mascota mascota : mascotas) {
                    System.out.println(VColores.PURPLE + "- " + mascota.toString()+ VColores.RESET);
                }
            }
        }
    }

    public void agregarMascota(Usuario logueado) {
        if (!(logueado instanceof Responsable)) {
            System.out.println(VColores.ROSA+"El usuario no es un responsable."+VColores.RESET);
        } else {
            String nombreMascota = vistaMascota.getNombreMascota();
            String domicilio = vistaMascota.getDomicilio();
            int cp = vistaMascota.getCP();
            ArrayList<Responsable> responsables = new ArrayList<>();
            responsables.add((Responsable) logueado);
            String descripcion = vistaMascota.getDescripcion();
            String RIAC = vistaMascota.getRIAC();
            String numero_poliza = vistaMascota.getNumeroPoliza();
            Mascota mascota = null;
            for (Mascota m : logueado.getMascotas()) {
                if (m.getNombre().equals(nombreMascota)) {
                    mascota = m;
                }
            }
            if (mascota == null) {
                if (vistaMascota.getExotico()) {
                    String certificado = vistaMascota.getCertificado();
                    ((Responsable) logueado).addMascota(new Animal_exotico(nombreMascota, domicilio, descripcion, RIAC, numero_poliza, certificado));
                } else
                    ((Responsable) logueado).addMascota(new Mascota(nombreMascota, domicilio, descripcion, RIAC, numero_poliza));
            } else {
                System.out.println(VColores.ROSA + "Mascota ya añadida. Asegúrese de que el nombre de la mascota sea correcto."+VColores.RESET);
            }
        }
    }

    public Usuario login(String identificador) {
        for (Responsable r : listaresponsable
        ) {
            if (r.getId().equals(identificador))
                return r;
        }
        return null;
    }

    public void crearUsuario() {
        String identificador = ExternalRRSS.LoginRRSS();
        String nombre = vistaResponsable.getNombre();
        if (validarUsuario(identificador, nombre)) {
            listaresponsable.add(new Responsable(identificador, nombre, TPlataforma.FACEBOOK));
        }
    }

    private boolean validarUsuario(String identificador, String nombre) {
        if (identificador == null)
            return false;

        if (login(identificador) != null)
            return false;

        if (hermana.login(identificador) != null)
            return false;

        if (nombre.isEmpty())
            return false;

        return true;
    }

    public void agregarResponsable(Responsable responsable) {
        listaresponsable.add(responsable);
    }
}