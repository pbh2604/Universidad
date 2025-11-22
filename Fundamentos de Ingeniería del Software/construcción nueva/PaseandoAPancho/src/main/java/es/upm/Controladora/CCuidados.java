package es.upm.Controladora;

import es.upm.Modelo.*;
import es.upm.Vista.IVistas.IVistaCuidados;
import es.upm.Vista.VColores;
import es.upm.Vista.VCuidados;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class CCuidados {
    private IVistaCuidados vistaCuidados;
    private List<Cuidado> listCuidados;

    public List<Cuidado> getListCuidados() {
        return listCuidados;
    }

    public void setListCuidados(List<Cuidado> listCuidados) {
        this.listCuidados = listCuidados;
    }

    public IVistaCuidados getVistaCuidados() {
        return vistaCuidados;
    }

    public void setVistaCuidados(IVistaCuidados vistaCuidados) {
        this.vistaCuidados = vistaCuidados;
    }

    public CCuidados() {
        this.vistaCuidados = new VCuidados();
        this.listCuidados = new LinkedList<>();
    }

    public void publicarCuidado(Usuario logueado) {
        if (!(logueado instanceof Responsable)) {
            System.out.println(VColores.ROSA + "El usuario no es un responsable."+VColores.RESET);
        } else {
            String nombreMascota = vistaCuidados.getNombreMascota();
            int cp = vistaCuidados.getCP();
            long fecha = vistaCuidados.getFecha();
            int duracion = vistaCuidados.getDuracion();
            ArrayList<Responsable> responsables = new ArrayList<>();
            responsables.add((Responsable) logueado);

            Mascota mascota = null;
            for (Mascota m : logueado.getMascotas()) {
                if (m.getNombre().equals(nombreMascota)) {
                    mascota = m;
                }
            }
            if (mascota == null) {
                System.out.println(VColores.PURPLE + "Mascota no encontrada. Asegúrese de que el nombre de la mascota sea correcto."+VColores.RESET);
            } else {
                Cuidado nuevoCuidado = new Cuidado(0.0, 0, fecha, duracion, cp, responsables, null, null, mascota);
                ((Responsable) logueado).setCuidado(nuevoCuidado);
                listCuidados.add(nuevoCuidado);
                System.out.println(VColores.ROSA + "Cuidado para la mascota " + nombreMascota + " publicado exitosamente."+VColores.RESET);
            }
        }
    }


    public void buscarCuidados(Usuario logueado) {
        if (!(logueado instanceof Cuidador)) {
            System.out.println(VColores.ROSA + "El usuario no es un cuidador."+VColores.RESET);
        } else {
            List<Cuidado> cuidadosPosibles = listCuidados;
            if (cuidadosPosibles.isEmpty())
                System.out.println(VColores.PURPLE +"No hay cuidados disponibles"+VColores.RESET);
            else {
                System.out.println(VColores.ROSA+"Cuidados: "+VColores.RESET);
                for (Cuidado cuidado : cuidadosPosibles) {
                    if (cuidado.getCuidador() == null && cuidado.getFecha() > System.currentTimeMillis())
                        System.out.println(VColores.PURPLE +cuidado.toString()+VColores.RESET);
                }
            }
        }
    }

    public void agregarCuidado(Cuidado nuevoCuidado) {
        listCuidados.add(nuevoCuidado);
    }
}
