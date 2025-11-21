#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

// Inclusión de los módulos necesarios para crear la simulación:
// - core: funciones principales y temporizador
// - network: estructura de red
// - internet: pila de protocolos
// - point-to-point: enlaces punto a punto
// - applications: clientes y servidores UDP
// - netanim: animaciones para NetAnim

using namespace ns3;

// Definición de un componente de log para la depuración
NS_LOG_COMPONENT_DEFINE("GemeloDigitalAtaqueDos");

// Función para monitorizar el estado del nodo (router/servidor) y detectar saturación
void MonitorizarEstado(Ptr<Node> nodoObjetivo, AnimationInterface* animacion, uint32_t idNodo){
    static bool estaSaturado = false; // bandera que indica si ya se detectó saturación
    static uint32_t vecesVerificado = 0; // número de verificaciones realizadas

    // Se simula saturación si han pasado más de 5 segundos
    if (Simulator::Now().GetSeconds() > 5.0 && !estaSaturado){
        animacion->UpdateNodeColor(idNodo, 255, 0, 0); // cambia el nodo a rojo
        animacion->UpdateNodeDescription(idNodo, "SATURADO"); // etiqueta visual
        estaSaturado = true;
    } else if (!estaSaturado){
        animacion->UpdateNodeColor(idNodo, 0, 255, 0); // verde si no está saturado
        animacion->UpdateNodeDescription(idNodo, "NORMAL");
    }

    // Repetir chequeo cada segundo, hasta 10 veces
    if (vecesVerificado++ < 10) 
        Simulator::Schedule(Seconds(1.0), &MonitorizarEstado, nodoObjetivo, animacion, idNodo);
}

int main(int argc, char *argv[]){
    Time::SetResolution(Time::NS); // Resolución de tiempo en nanosegundos

    // Crear nodos: 2 clientes, 1 atacante y 1 servidor
    NodeContainer nodosUsuarios, nodoAtacante, nodoServidor;
    nodosUsuarios.Create(2);
    nodoAtacante.Create(1);
    nodoServidor.Create(1);

    // Instalar la pila de protocolos en todos los nodos
    InternetStackHelper pilaProtocolo;
    pilaProtocolo.Install(nodosUsuarios);
    pilaProtocolo.Install(nodoAtacante);
    pilaProtocolo.Install(nodoServidor);

    // Configurar enlaces punto a punto
    PointToPointHelper enlacePuntoAPunto;
    enlacePuntoAPunto.SetDeviceAttribute("DataRate", StringValue("10Mbps")); // velocidad
    enlacePuntoAPunto.SetChannelAttribute("Delay", StringValue("2ms")); // retardo

    // Conectar los nodos con el servidor
    NetDeviceContainer enlaceCliente1 = enlacePuntoAPunto.Install(nodosUsuarios.Get(0), nodoServidor.Get(0));
    NetDeviceContainer enlaceCliente2 = enlacePuntoAPunto.Install(nodosUsuarios.Get(1), nodoServidor.Get(0));
    NetDeviceContainer enlaceAtaque = enlacePuntoAPunto.Install(nodoAtacante.Get(0), nodoServidor.Get(0));

    // Asignar direcciones IP a cada enlace
    Ipv4AddressHelper direccionamiento;
    direccionamiento.SetBase("10.10.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaz1 = direccionamiento.Assign(enlaceCliente1);
    direccionamiento.SetBase("10.10.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaz2 = direccionamiento.Assign(enlaceCliente2);
    direccionamiento.SetBase("10.10.3.0", "255.255.255.0");
    Ipv4InterfaceContainer interfazAtaque = direccionamiento.Assign(enlaceAtaque);

    // Crear servidor UDP en el nodo servidor
    UdpServerHelper servidorUdp(4000);
    ApplicationContainer appServidor = servidorUdp.Install(nodoServidor.Get(0));
    appServidor.Start(Seconds(1.0));
    appServidor.Stop(Seconds(10.0));

    // Cliente 1: tráfico normal
    UdpClientHelper usuario1(interfaz1.GetAddress(1), 4000);
    usuario1.SetAttribute("MaxPackets", UintegerValue(50));
    usuario1.SetAttribute("Interval", TimeValue(MilliSeconds(100)));
    usuario1.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer appUsuario1 = usuario1.Install(nodosUsuarios.Get(0));

    // Cliente 2: tráfico normal
    UdpClientHelper usuario2(interfaz2.GetAddress(1), 4000);
    usuario2.SetAttribute("MaxPackets", UintegerValue(50));
    usuario2.SetAttribute("Interval", TimeValue(MilliSeconds(100)));
    usuario2.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer appUsuario2 = usuario2.Install(nodosUsuarios.Get(1));

    // Nodo atacante: tráfico masivo (DoS)
    UdpClientHelper appAtaque(interfazAtaque.GetAddress(1), 4000);
    appAtaque.SetAttribute("MaxPackets", UintegerValue(1000000));
    appAtaque.SetAttribute("Interval", TimeValue(MilliSeconds(1)));
    appAtaque.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer appAtacante = appAtaque.Install(nodoAtacante.Get(0));

    // Iniciar aplicaciones
    appUsuario1.Start(Seconds(2.0));
    appUsuario2.Start(Seconds(2.5));
    appAtacante.Start(Seconds(3.0));
    appAtacante.Stop(Seconds(10.0));

    // Generar tablas de rutas automáticas
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Crear archivo XML para animación
    AnimationInterface animacion("gemelo_digital_ataque.xml");

    // Posicionar los nodos para visualización en NetAnim
    animacion.SetConstantPosition(nodosUsuarios.Get(0), 10.0, 10.0);
    animacion.SetConstantPosition(nodosUsuarios.Get(1), 10.0, 30.0);
    animacion.SetConstantPosition(nodoAtacante.Get(0), 10.0, 50.0);
    animacion.SetConstantPosition(nodoServidor.Get(0), 50.0, 30.0);

    // Iniciar sistema de monitoreo visual de saturación
    Simulator::Schedule(Seconds(2.0), &MonitorizarEstado, nodoServidor.Get(0), &animacion, nodoServidor.Get(0)->GetId());

    // Ejecutar simulación
    Simulator::Stop(Seconds(11.0));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
