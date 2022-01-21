import {WEB_SOCKET_ROOT} from '../../api/endpoints';
import {FormLoader, SectionContent} from '../../components';
import {useWs} from '../../utils';
import {Typography} from '@mui/material';
import {MQBState} from '../types';
import {FC} from 'react';

const MQB_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "MQBState";

const MqbStatus: FC = () => {
    const {connected, updateData, data} = useWs<MQBState>(MQB_SETTINGS_WEBSOCKET_URL);


    const content = () => {
        if (!connected || !data) {
            return (<FormLoader message="Connecting to WebSocket…"/>);
        }
        return (
            <>
                <div>Button State: {data.lastKeyPressed}</div>
            </>
        );
    };

    return (
        <>
            <SectionContent title='MQB Status' titleGutter>
                <Typography variant="body1" paragraph>
                    {content()}
                </Typography>
            </SectionContent>
        </>
    );
};

export default MqbStatus;
