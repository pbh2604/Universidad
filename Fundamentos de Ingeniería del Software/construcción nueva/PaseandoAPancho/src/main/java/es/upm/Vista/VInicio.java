package es.upm.Vista;

import es.upm.Vista.IVistas.IVistaInicio;

public class VInicio implements IVistaInicio {
    public VInicio() {
    }
    public static void setMessageerror(String usuario_no_registrado) {
        System.err.println(usuario_no_registrado);
    }

    public void mostrarInicio() {
        System.out.println(VColores.BLUE + "***** CuidandoAPancho - unimos cuidadores y mascotas ******" +
                VColores.WHITE +"\nSeleccione una de las siguientes opciones:\n" +VColores.CYAN+
                "0.Exit\n" +
                "1.Login\n" +
                "2.Quiero que cuiden a mi mascota\n" +
                "3.Quiero cuidar mascotas"+VColores.RESET);
    }

    public void mostrarOpciones() {
        System.out.println(VColores.BLUE +"***** Opciones ******" +
                VColores.WHITE +"\nSeleccione una de las siguientes opciones:" +VColores.CYAN+
                "\n0.Exit\n" +
                "1.Listar mis mascotas\n" +
                "2.Listar mis cuidados\n" +
                "3.Crear petición de cuidado a mis mascotas\n" +
                "4.Dar de alta a mi mascota\n" +
                "5.Buscar cuidados\n"+VColores.RESET);
    }
}
