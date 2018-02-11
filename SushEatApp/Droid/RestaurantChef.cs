using System;
using System.Collections.Generic;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Widget;
using Microsoft.WindowsAzure.Storage; // Namespace for CloudStorageAccount
using Microsoft.WindowsAzure.Storage.Table; // Namespace for Table storage types

namespace SushEat.Droid
{
    [Activity(Label = "Incoming orders")]
    public class RestaurantChef : MainActivity
    {
        ListView listOfOrders;
        public List<String> incomingOrders;
        public List<Customer> customerList;
        public static int currentOrder = -1;

        protected override async void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            SetContentView(Resource.Layout.incomingOrders);
            
            listOfOrders = FindViewById<ListView>(Resource.Id.order_list);
            Button refresh = FindViewById<Android.Widget.Button>(Resource.Id.refresh);

            customerList = new List<Customer>();
            incomingOrders = new List<String>();

            TableQuery<Customer> query = new TableQuery<Customer>().Where(TableQuery.GenerateFilterCondition("PartitionKey", QueryComparisons.Equal, "ORDERED"));
            TableContinuationToken continuationToken = null;

            refresh.Click += delegate
            {
                this.Recreate();
            };

            listOfOrders.ItemClick += listOfOrders_ItemClick;

            
            do
            {
                try
                {
                    TableQuerySegment<Customer> tableQueryResult = await table.ExecuteQuerySegmentedAsync(query, continuationToken);
                    continuationToken = tableQueryResult.ContinuationToken;

                    foreach (Customer customer in tableQueryResult.Results)
                    {
                        customerList.Add(customer);
                        incomingOrders.Add(customer.Sorder);
                    }
                    var incomingOrdersArray = incomingOrders.ToArray();
                    listOfOrders.Adapter = new ArrayAdapter<string>(this, Android.Resource.Layout.SimpleListItem1, incomingOrdersArray);
                    listOfOrders.DeferNotifyDataSetChanged();

                }
                catch (Exception e)
                {
                    Toast.MakeText(this, e.Message, ToastLength.Long).Show();
                }
                
            } while (continuationToken != null);


        }

        void listOfOrders_ItemClick(object sender, AdapterView.ItemClickEventArgs e)
        {
            currentOrder = e.Position;
            var intent = new Intent(this, typeof(processOrder));
            this.Finish();
            StartActivity(intent);
        }
    }

    
}