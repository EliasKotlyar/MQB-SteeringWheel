import {WEB_SOCKET_ROOT} from '../../api/endpoints';
import {FormLoader, SectionContent} from '../../components';
//import {useDebugWS} from '../../utils';
import {Typography} from '@mui/material';
import {DebugState} from '../types';
import {FC, useCallback, useEffect, useState} from 'react';
import Sockette from "sockette";
import {addAccessTokenParameter} from "../../api/authentication";

const DEBUGSTATE = WEB_SOCKET_ROOT + "DebugState";

interface WebSocketIdMessage {
    type: "id";
    id: string;
}

interface WebSocketPayloadMessage<DebugState> {
    type: "payload";
    origin_id: string;
    payload: DebugState;
}


type WebSocketMessage<DebugState> = WebSocketIdMessage | WebSocketPayloadMessage<DebugState>;

const Debug: FC = () => {
    //const {connected, updateData, data} = useDebugWS<DebugState>(DEBUGSTATE);

    const [data, setData] = useState<Array<DebugState>>([]);
    const [connected, setConnected] = useState<boolean>(false);


    const setDataElements = (dataElement: DebugState) => {
        let dataArray: Array<DebugState> = [dataElement];
        setData((prevState) => {
            let retArray = [...prevState]
            let item = retArray.find(element => dataElement.protectedId == element.protectedId);
            if (item === undefined) {
                retArray.push(dataElement);
            } else {
                item.buffer = dataElement.buffer
            }
            return retArray;
        });
    }
    useEffect(() => {
        /*
        setTimeout(() => {
            let dataElement: DebugState = {
                protectedId: String(Math.floor(Math.random() * 10)),
                buffer: String(Math.floor(Math.random() * 10)),
                enabled: true
            };
            setDataElements(dataElement);
        }, 500);
         */
    }, [data]);


    const onMessage = useCallback((event: MessageEvent) => {
        const rawData = event.data;
        if (typeof rawData === 'string' || rawData instanceof String) {
            const message = JSON.parse(rawData as string) as WebSocketMessage<DebugState>;
            switch (message.type) {
                case "id":

                    break;
                case "payload":
                    let dataElement: DebugState = message.payload;
                    setDataElements(dataElement);
                    break;
            }
        }
    }, []);
    useEffect(() => {
        const instance = new Sockette(addAccessTokenParameter(DEBUGSTATE), {
            onmessage: onMessage,
            onopen: () => {
                setConnected(true);
            },
            onclose: () => {
                setConnected(false);

            },
        });
    }, [onMessage]);


    const content = () => {

        if (!connected || !data) {
            return (<FormLoader message="Connecting to WebSocket…"/>);
        }

        return (
            <>
                {data.map((currentElement) => (
                    <>
                        <div>Protected ID : {currentElement.protectedId}</div>
                        <div>Buffer: {currentElement.buffer}</div>

                    </>
                ))}
            </>
        );
    }

    return (
        <>
            <SectionContent title='Debug Status' titleGutter>
                <Typography variant="body1" paragraph>
                    {content()}
                </Typography>
            </SectionContent>
        </>
    );
};

export default Debug;
