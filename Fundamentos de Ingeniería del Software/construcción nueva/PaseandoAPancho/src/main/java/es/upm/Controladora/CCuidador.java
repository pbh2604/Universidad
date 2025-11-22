package es.upm.Controladora;

import es.upm.Modelo.*;
import es.upm.Vista.IVistas.IVistaCuidador;
import es.upm.Vista.VColores;
import es.upm.Vista.VCuidador;
import servidor.ExternalRRSS;
import java.util.LinkedList;
import java.util.List;

public class CCuidador {

    private List<Cuidador> listaCuida;
    private IVistaCuidador vistaCuidador;
    private CResponsable hermana;

    public List<Cuidador> getListaCuida() {
        return listaCuida;
    }

    public void setListaCuida(List<Cuidador> listaCuida) {
        this.listaCuida = listaCuida;
    }

    public IVistaCuidador getVistaCuidador() {
        return vistaCuidador;
    }

    public void setVistaCuidador(IVistaCuidador vistaCuidador) {
        this.vistaCuidador = vistaCuidador;
    }

    public CResponsable getHermana() {
        return hermana;
    }

    public void setHermana(CResponsable hermana) {
        this.hermana = hermana;
    }

    public CCuidador() {
        this.vistaCuidador = new VCuidador();
        listaCuida = new LinkedList<>();
    }

    public void setcResponsable(CResponsable hermana) {
        this.hermana = hermana;
    }

    public void listarCuidados(Usuario logueado) {
        if (!(logueado instanceof Cuidador)) {
            System.out.println(VColores.ROSA+"El usuario no es un cuidador."+VColores.RESET);
        } else {
            Cuidador cuidador = (Cuidador) logueado;
            List<Cuidado> cuidadosDelCuidador = cuidador.getCuidados();
            if (cuidadosDelCuidador.isEmpty()) {
                System.out.println(VColores.PURPLE +"No tienes cuidados anteriores."+VColores.RESET);
            } else {
                System.out.println(VColores.ROSA+"Tus cuidados:"+VColores.RESET);
                for (Cuidado cuidado : cuidadosDelCuidador) {
                    System.out.println(VColores.PURPLE +cuidado.toString()+VColores.RESET);
                }
            }
        }
    }

    public Usuario login(String identificador) {
        for (Cuidador r : listaCuida
        ) {
            if (r.getId().equals(identificador))
                return r;
        }
        return null;
    }

    public void crearUsuario() {
        String identificador = ExternalRRSS.LoginRRSS();
        String nombre = vistaCuidador.getNombre();
        if (valida(identificador, nombre)) {
            listaCuida.add(new Cuidador(identificador, nombre, TPlataforma.FACEBOOK));
        }
    }

    private boolean valida(String identificador, String nombre) {
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

    public void agregarCuidador(Cuidador cuidador) {
        listaCuida.add(cuidador);
    }
}
