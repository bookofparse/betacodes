/*
 * Copyright (c) 2015-present, Parse, LLC.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.parse.activity;

import android.app.DatePickerDialog;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Toast;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;
import com.parse.FindCallback;
import com.parse.ParseAnalytics;
import com.parse.ParseException;
import com.parse.ParseObject;
import com.parse.ParseQuery;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;


public class MainActivity extends ActionBarActivity {
  Button btBegin,btEnd;
  EditText etId,etName;
  int year,month,day;
  View currentBtn;
  String activityClassName = "iot_dog";

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    ParseAnalytics.trackAppOpenedInBackground(getIntent());
    initView();
    dateInit();
  }
  private void initView()
  {
    btBegin = (Button)findViewById(R.id.btBegin);
    btEnd = (Button)findViewById(R.id.btEnd);
    etId = (EditText)findViewById(R.id.etUsrId);
    etName = (EditText)findViewById(R.id.etDogName);
    etId.setText("test_1");
    etName.setText("dog_1");
  }
  private void dateInit()
  {
    GregorianCalendar calendar = new GregorianCalendar();
    year = calendar.get(Calendar.YEAR);
    month = calendar.get(Calendar.MONTH);
    day= calendar.get(Calendar.DAY_OF_MONTH);

    btBegin.setText(year + "/" + (month + 1) + "/" + day);
    btEnd.setText(year + "/" + (month + 1) + "/" + day);
  }

  public void btLoad(View view)
  {
    getData();
  }
  private void getData()
  {
    ParseQuery<ParseObject> query = ParseQuery.getQuery(activityClassName);
    query.whereEqualTo("usrId",etId.getText().toString());
    query.whereEqualTo("dogName", etName.getText().toString());

    String beginDateStr[] = btBegin.getText().toString().split("/");
    String endDateStr[] = btEnd.getText().toString().split("/");

    Calendar beginCal = Calendar.getInstance();
    Calendar endCal = Calendar.getInstance();

    beginCal.set(Integer.parseInt(beginDateStr[0]),
                  Integer.parseInt(beginDateStr[1])-1,
                  Integer.parseInt(beginDateStr[2]),0,0,0);
    endCal.set(Integer.parseInt(endDateStr[0]),
            Integer.parseInt(endDateStr[1])-1,
            Integer.parseInt(endDateStr[2]),23,59,59);

    query.whereGreaterThanOrEqualTo("updatedAt", beginCal.getTime());
    query.whereLessThanOrEqualTo("updatedAt", endCal.getTime());
    query.addAscendingOrder("updatedAt");

    query.findInBackground(new FindCallback<ParseObject>() {
      @Override
      public void done(List<ParseObject> list, ParseException e) {
        Toast.makeText(getApplicationContext(), list.size() + " data", Toast.LENGTH_LONG).show();
        setChartData(list);
      }
    });
  }
  private void setChartData(List<ParseObject> list)
  {
    if(list.size() == 0)
      return;

    LineChart chart = (LineChart) findViewById(R.id.chart);
    ArrayList<Entry> valsComp1 = new ArrayList<Entry>();
    ArrayList<String> xVals = new ArrayList<String>();
    int index = 0;
    DateFormat format = new SimpleDateFormat("MM/dd:hh:mm");

    for(ParseObject obj : list)
    {
      Entry c1e1 = new Entry((float)obj.getDouble("activity"), index);
      valsComp1.add(c1e1);

      xVals.add(format.format(obj.getUpdatedAt()));
      index++;
    }

    LineDataSet setComp1 = new LineDataSet(valsComp1, "Activity");
    setComp1.setAxisDependency(YAxis.AxisDependency.LEFT);

    ArrayList<ILineDataSet> dataSets = new ArrayList<ILineDataSet>();
    dataSets.add(setComp1);

    LineData data = new LineData(xVals, dataSets);
    chart.setData(data);
    chart.invalidate(); // refresh
  }
  public void btDateClick(View view)
  {
    currentBtn = view;
    new DatePickerDialog(MainActivity.this, dateSetListener, year, month, day).show();
  }
  private DatePickerDialog.OnDateSetListener dateSetListener = new DatePickerDialog.OnDateSetListener() {

    @Override
    public void onDateSet(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
      String msg = String.format("%d/%d/%d", year, monthOfYear + 1, dayOfMonth);
      ((Button)currentBtn).setText(msg);
    }
  };




  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    // Inflate the menu; this adds items to the action bar if it is present.
    getMenuInflater().inflate(R.menu.menu_main, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
    // Handle action bar item clicks here. The action bar will
    // automatically handle clicks on the Home/Up button, so long
    // as you specify a parent activity in AndroidManifest.xml.
    int id = item.getItemId();

    //noinspection SimplifiableIfStatement
    if (id == R.id.action_settings) {
      return true;
    }

    return super.onOptionsItemSelected(item);
  }
}
