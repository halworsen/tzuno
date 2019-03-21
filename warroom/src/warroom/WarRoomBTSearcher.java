package warroom;

import java.io.IOException;

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

    private RemoteDevice btDevice;
    private String btUrl;

    private WarRoomController controller;
    private boolean scanFinished = false;


    WarRoomBTSearcher(WarRoomController controller) {
        this.controller = controller;
    }

    @Override
    protected Void call() throws BluetoothStateException {
        scanFinished = false;

        // Søk etter bluetooth-enheten til Arduinoen
        controller.log("Searching for bluetooth devices...");
        LocalDevice.getLocalDevice().getDiscoveryAgent().startInquiry(DiscoveryAgent.GIAC, new DiscoveryListener() {
            @Override
            public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                try {
                    String name = btDevice.getFriendlyName(false);
                    if (name.equals("PLabTzuno")) {
                        WarRoomBTSearcher.this.btDevice = btDevice;
                        controller.log("Tzuno found! Connecting...");
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

        controller.log("Searching for service...");
        LocalDevice.getLocalDevice().getDiscoveryAgent().searchServices(attrIDs, searchUuidSet,
                btDevice, new DiscoveryListener() {
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
                            btUrl = servRecord[i].getConnectionURL(ServiceRecord.AUTHENTICATE_NOENCRYPT, false);
                            if (btUrl != null) {
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

        controller.log("Tzuno address: " + btDevice.getBluetoothAddress());
        controller.log("Tzuno URL: " + btUrl);

        StreamConnection streamConnection;
        try {
            streamConnection = (StreamConnection) Connector.open(btUrl);
            controller.setStream(streamConnection);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }

        return null;
    }
}
