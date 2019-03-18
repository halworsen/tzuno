package warroom;

import java.io.IOException;
import java.io.InputStream;

import javax.bluetooth.BluetoothStateException;
import javax.bluetooth.DeviceClass;
import javax.bluetooth.DiscoveryAgent;
import javax.bluetooth.DiscoveryListener;
import javax.bluetooth.LocalDevice;
import javax.bluetooth.RemoteDevice;
import javax.bluetooth.ServiceRecord;
import javax.bluetooth.UUID;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;

import javafx.concurrent.Task;

public class WarRoomBTSearcher extends Task<Void>{

    private RemoteDevice hc05device;
    private String hc05Url;

    private WarRoomController controller;
    private boolean scanFinished = false;


    WarRoomBTSearcher(WarRoomController controller) {
        this.controller = controller;
    }

    @Override
    protected Void call() throws BluetoothStateException {
        scanFinished = false;

        // Søk etter bluetooth-enheten (HC-05) til Arduinoen
        LocalDevice.getLocalDevice().getDiscoveryAgent().startInquiry(DiscoveryAgent.GIAC, new DiscoveryListener() {
            @Override
            public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                try {
                    String name = btDevice.getFriendlyName(false);
                    System.out.format("%s (%s)\n", name, btDevice.getBluetoothAddress());
                    if (name.matches("HC.*")) {
                        hc05device = btDevice;
                        System.out.println("Bluetooth device found!");
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void inquiryCompleted(int discType) {
                scanFinished = true;
            }

            @Override
            public void serviceSearchCompleted(int transID, int respCode) {
            }

            @Override
            public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
            }
        });

        while (!scanFinished) {
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
                return null;
            }
        }

        // Finn tjenesten
        UUID uuid = new UUID(0x1101);
        UUID[] searchUuidSet = new UUID[]{uuid};
        int[] attrIDs = new int[]{
                0x0100
        };

        scanFinished = false;

        LocalDevice.getLocalDevice().getDiscoveryAgent().searchServices(attrIDs, searchUuidSet,
                hc05device, new DiscoveryListener() {
                    @Override
                    public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                    }

                    @Override
                    public void inquiryCompleted(int discType) {
                    }

                    @Override
                    public void serviceSearchCompleted(int transID, int respCode) {
                        scanFinished = true;
                    }

                    @Override
                    public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
                        for (int i = 0; i < servRecord.length; i++) {
                            hc05Url = servRecord[i].getConnectionURL(ServiceRecord.AUTHENTICATE_NOENCRYPT, false);
                            if (hc05Url != null) {
                                break; //take the first one
                            }
                        }
                    }
                });

        while (!scanFinished) {
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                return null;
            }
        }

        System.out.println(hc05device.getBluetoothAddress());
        System.out.println(hc05Url);

        StreamConnection streamConnection;
        try {
            streamConnection = (StreamConnection) Connector.open(hc05Url);
            controller.setStream(streamConnection);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }

        return null;
    }
}
