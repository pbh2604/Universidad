package es.upm.Modelo.Interfaces;

import es.upm.Modelo.Mascota;
import java.util.List;

public interface IUsuario {
    String getNombre();
    List<Mascota> getMascotas(); // <T>
}
