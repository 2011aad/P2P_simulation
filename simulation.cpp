
#include "simulation.h"

void Simulation::run(){

    //initialize file_queue using (#approximate_mean_queue_length) files
    //initialize serv_pool using (#approximate_mean_server_number) servers
    double start_file_number = (1+mu_c/mu_s)*(lambda_c/(lambda_s*mu_c/mu_s-lambda_c));
    double start_server_number = lambda_s/mu_s;

    double system_time = 0;

    for(int i=0;i<start_file_number;++i){
        file_queue.add(File(numOfBlock));
    }

    for(int i=0;i<start_server_number;++i){
        Server s(mu_c*numOfBlock, mu_s, system_time);
        event_queue.push(Event(Event::SERVER_LEAVE, s.leave_time, -1, serv_pool.add(s)));
    }

    //create a server arrival event and a file arrival event, later arrivals occurs after handling current arrival events
    expdist = exponential_distribution<double>(lambda_s);
    event_queue.push(Event(Event::SERVER_ARRIVAL, system_time + expdist(rand_engine)));

    expdist = exponential_distribution<double>(lambda_c);
    event_queue.push(Event(Event::FILE_ARRIVAL, system_time + expdist(rand_engine)));


    //handling (#iteration) number of files
    for(int iteration=0;iteration<numOfFile;++iteration){
        if(iteration%1000==0){
            cout<<"iteration: "<<iteration<<endl;
            cout<<"   Mean queue length: "<<meanQueueLength()<<endl;
        }

        //waiting for a file arrival
        while(file_queue.empty()){
            auto e = event_queue.top();
            event_queue.pop();

            system_time = e.getTime();

            if(e.event_type==Event::SERVER_ARRIVAL){
                Observe();
                Server s(mu_c*numOfBlock, mu_s, system_time);
                event_queue.push(Event(Event::SERVER_LEAVE, s.leave_time, -1, serv_pool.add(s)));
                expdist = exponential_distribution<double>(lambda_s);
                event_queue.push(Event(Event::SERVER_ARRIVAL, system_time + expdist(rand_engine)));
            }
            else if(e.event_type==Event::FILE_ARRIVAL){
                if(file_queue.size()<50*start_file_number){
                    file_queue.add(File(numOfBlock));
                }
                expdist = exponential_distribution<double>(lambda_c);
                event_queue.push(Event(Event::FILE_ARRIVAL, system_time + expdist(rand_engine)));
            }
            else if(e.event_type==Event::SERVER_LEAVE){
                serv_pool.remove(e.server_index);
            }
        }

        // a file arrives
        File f = file_queue.front();
        file_queue.remove_front();

        //event queue initialization:
        //assign servers to each blocks, if the block can be served before server leaving, create a BLOCK_SERVED event
        //otherwise create a RELEASE_BLOCK event, and the block will be released after the server leaving
        while(f.hasEmptyBlock() && serv_pool.hasFreeServer()){
            Server s = serv_pool.getServer();
            Block b = f.getEmptyBlock();
            auto time_success_pair = s.upload(system_time, b);
            if(time_success_pair.second){
                event_queue.push(Event(Event::BLOCK_SERVED, time_success_pair.first, b, s.id));
            }
            else{
                event_queue.push(Event(Event::RELEASE_BLOCK, time_success_pair.first, b));
            }
        }

        //file serve process
        while(!f.allBlockServed()){
            auto e = event_queue.top();
            event_queue.pop();

            system_time = e.getTime();

            //handling SERVER_ARRIVAL event: create another SERVER_ARRIVAL event
            if(e.event_type==Event::SERVER_ARRIVAL){
                Observe();
                Server s(mu_c*numOfBlock, mu_s, system_time);
                event_queue.push(Event(Event::SERVER_LEAVE, s.leave_time, -1, serv_pool.add(s)));
                expdist = exponential_distribution<double>(lambda_s);
                event_queue.push(Event(Event::SERVER_ARRIVAL, system_time + expdist(rand_engine)));
            }
            //handling FILE_ARRIVAL event: create another FILE_ARRIVAL event
            else if(e.event_type==Event::FILE_ARRIVAL){
                if(file_queue.size()<50*start_file_number){
                    file_queue.add(File(numOfBlock));
                }
                expdist = exponential_distribution<double>(lambda_c);
                event_queue.push(Event(Event::FILE_ARRIVAL, system_time + expdist(rand_engine)));
            }
            //handling BLOCK_SERVED event: the server get free and the block is served
            else if(e.event_type==Event::BLOCK_SERVED){
                serv_pool.free(e.server_index);
                f.blockServed(e.block);
            }
            //handling SERVER_LEAVE event: the server should be removed from the serv_pool
            else if(e.event_type==Event::SERVER_LEAVE){
                serv_pool.remove(e.server_index);
            }
            //handling RELEASE_BLOCK event: the block should be returned as not uploaded
            else if(e.event_type==Event::RELEASE_BLOCK){
                f.returnEmptyBlock(e.block);
            }

            //After handling an event, there may be (released or not assigned blocks) or (new arrival or freed server)
            while(f.hasEmptyBlock() && serv_pool.hasFreeServer()){
                Server s = serv_pool.getServer();
                Block b = f.getEmptyBlock();
                auto time_success_pair = s.upload(system_time, b);
                if(time_success_pair.second){
                    event_queue.push(Event(Event::BLOCK_SERVED, time_success_pair.first, b, s.id));
                }
                else{
                    event_queue.push(Event(Event::RELEASE_BLOCK, time_success_pair.first, b));
                }
            }
        }
    }
}


void Simulation::Observe(){
    ++observe_counter;
    total_queue_length += file_queue.size();
    total_server_number += serv_pool.serverNumber();
}
