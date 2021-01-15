package net.nametable.btkbremote;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.os.ParcelUuid;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.widget.PopupMenu;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.navigation.fragment.NavHostFragment;

import com.skydoves.powermenu.MenuAnimation;
import com.skydoves.powermenu.OnMenuItemClickListener;
import com.skydoves.powermenu.PowerMenu;
import com.skydoves.powermenu.PowerMenuItem;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.UUID;

public class FirstFragment extends Fragment {

    private PowerMenu mPowerMenu;
    private BluetoothSocket mBTSocket;
    private Set<BluetoothDevice> mBTDevices;
    private TextView mLabel;
    private Button mBtnSend;
    private EditText mTxtSend;

    @Override
    public View onCreateView(
            LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState
    ) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_first, container, false);
    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        mLabel = view.findViewById(R.id.textview_first);
        mBtnSend = view.findViewById(R.id.btn_send);
        mTxtSend = view.findViewById(R.id.txt_send);
        BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        mBTDevices = mBluetoothAdapter.getBondedDevices();

        List<PowerMenuItem> s = new ArrayList<PowerMenuItem>();
        for(BluetoothDevice bt : mBTDevices)
            s.add(new PowerMenuItem(bt.getName(), false));

        mPowerMenu = new PowerMenu.Builder(getContext())
                .addItemList(s) // list has "Novel", "Poerty", "Art"
                .setAnimation(MenuAnimation.SHOW_UP_CENTER)
                .setMenuRadius(5) // sets the corner radius.
                .setMenuShadow(10f) // sets the shadow.
                .setTextColor(ContextCompat.getColor(getContext(), R.color.purple_200))
                .setTextGravity(Gravity.CENTER)
                .setTextTypeface(Typeface.create("sans-serif-medium", Typeface.BOLD))
                .setSelectedTextColor(Color.WHITE)
                .setMenuColor(Color.WHITE)
                .setSelectedMenuColor(ContextCompat.getColor(getContext(), R.color.black))
                .setOnMenuItemClickListener((position, item) -> {
//                    NavHostFragment.findNavController(FirstFragment.this)
//                            .navigate(R.id.action_FirstFragment_to_SecondFragment);
                    String itemName = item.getTitle().toString();
                    for(BluetoothDevice bt : mBTDevices) {
                        String name = bt.getName();
                        if (name.equals(itemName)) {
                            ParcelUuid uuids[] = bt.getUuids();
                            try {
                                mBTSocket = bt.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"));
                                mBTSocket.connect();
                                mLabel.setText("Connected! Set text and send below");
                            } catch (IOException e) {
                                Log.d("[RFCOMM FAILED]", "Failed to connect to bluetooth device");
                            }

                        }
                    }
                    mPowerMenu.dismiss();
                })
                .build();



        view.findViewById(R.id.button_first).setOnClickListener(view12 -> mPowerMenu.showAsAnchorCenter(view12));

        mBtnSend.setOnClickListener(view1 -> {
            try {
                byte buf[] = mTxtSend.getText().toString().getBytes();
                mBTSocket.getOutputStream().write(buf);
                mBTSocket.getOutputStream().flush();
            } catch(IOException exception) {

            }

        });
    }
}